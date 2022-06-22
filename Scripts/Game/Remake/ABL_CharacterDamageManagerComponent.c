modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	ref map<string, string> ablSettings;
	
	const string ABL_FileNameJson = "ABL_Settings.json";
	const string ABL_MOD_ID = "59951797A291CA02";				//it's probably possible to get this in a better way but ok
	
	IEntity ownerChar;
	bool alreadyDestroyed = false;
	World worldTmp;

	
	ref static array<ref DecalWrapper> currentPlayerDecals;
	ref array<ref DecalWrapper> currentCharacterDecals;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		ownerChar = owner;
		auto world = owner.GetWorld();
		
		
		currentCharacterDecals = new ref array<ref DecalWrapper>();
		
		if (!currentPlayerDecals)
			currentPlayerDecals = new array<ref DecalWrapper>();
		
		worldTmp = GetGame().GetWorld();
		////////////////////////////////////////////////////////////////////////////////////////////////
		//Settings initialization stuff 
		MCF_SettingsManager ABL_mcfSettingsManager = MCF_SettingsManager.GetInstance();
		OrderedVariablesMap ablVariablesMap = new OrderedVariablesMap();
			
		ablVariablesMap.Set("waitTimeBetweenFrames", new VariableInfo("Wait Times between frames (in seconds)", "0.1"));
		ablVariablesMap.Set("diffOriginX", new VariableInfo("Diff Origin X (TEST)", "0"));
		ablVariablesMap.Set("diffOriginY", new VariableInfo("Diff Origin Y (TEST)", "0"));
		ablVariablesMap.Set("diffOriginZ", new VariableInfo("Diff Origin Z (TEST)", "0"));
		ablVariablesMap.Set("decalAngle", new VariableInfo("Decal Angle", "0"));
		ablVariablesMap.Set("nearClip", new VariableInfo("Near Clip (TEST)", "0"));
		ablVariablesMap.Set("farClip", new VariableInfo("Far Clip (TEST)", "2"));
		
		
		ablVariablesMap.Set("maxDecalsPerChar", new VariableInfo("Max Decals per Character", "2"));
		ablVariablesMap.Set("maxDecalsPlayerWeapon", new VariableInfo("Max Decals for Player Weapon", "6"));
		ablVariablesMap.Set("debugSpheres", new VariableInfo("Debug Spheres", "0"));
	
		if (!ABL_mcfSettingsManager.GetJsonManager(ABL_MOD_ID))
			ablSettings = ABL_mcfSettingsManager.Setup(ABL_MOD_ID, ABL_FileNameJson, ablVariablesMap);
		else if (!ablSettings)
		{
			ablSettings = ABL_mcfSettingsManager.GetModSettings(ABL_MOD_ID);
			ABL_mcfSettingsManager.GetJsonManager(ABL_MOD_ID).SetUserHelpers(ablVariablesMap);
				
		}
			
	
		//////////////////////////////////////////////////////////////////////////////////////////////////
		
		
	}

	override void OnDamage(
			EDamageType type,
			float damage,
			HitZone pHitZone,
			IEntity instigator,
			inout vector hitTransform[3],
			float speed,
			int colliderID,
			int nodeID)
	{
		super.OnDamage(type, damage, pHitZone, instigator, hitTransform, speed, colliderID, nodeID);
			
		ABL_AnimatedDecalManager tempManager;		//todo move this away
		tempManager = ABL_AnimatedDecalManager.GetInstance();
		
		
		
		ablSettings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);


		array<string> boneNames = new array<string>();
		ownerChar.GetBoneNames(boneNames);
		
		//we've got the local node id, we need the external one though. So.
		vector testVec[4];
		vector test1[4];
		
		int correctBoneIndex
		int correctNodeId;

		int colliderDescriptorIndex = pHitZone.GetColliderDescriptorIndex(colliderID);

		pHitZone.TryGetColliderDescription(ownerChar, colliderDescriptorIndex, test1, correctBoneIndex, correctNodeId);
		
		
		if (!tempManager)
			tempManager = ABL_AnimatedDecalManager.Cast(GetGame().SpawnEntity(ABL_AnimatedDecalManager, GetGame().GetWorld(), null));
			
		
		Print(pHitZone.GetName());
		if (hitTransform[0].Length() != 0)
		{
			if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
			{
				//Print("Start blood");
				
				// we need to get the angle before he dies 
				GetGame().GetCallqueue().CallLater(tempManager.StartNewAnimation, 2000, false, ownerChar, hitTransform[0], hitTransform[1], EDecalType.BLOODPOOL, true, 1.5, correctNodeId);
				alreadyDestroyed = true;		//only once
			}
			else if (damage > 20.0)
				tempManager.StartNewAnimation(ownerChar,  hitTransform[0],  hitTransform[1], EDecalType.GENERIC_SPLATTER, false, 0.0, correctNodeId);
		
			
			/* WEAPON SPLATTERS */
			PlayerManager pMan = GetGame().GetPlayerManager();
			SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			IEntity currentPlayer = m_playerController.GetMainEntity();
			vector playerTransform[4];

			currentPlayer.GetTransform(playerTransform);
			//Print("Applying Decal on damaged entity");
			
			int maxDecalsPerChar = ablSettings.Get("maxDecalsPerChar").ToInt();
			ManageDecalStack(currentCharacterDecals, ownerChar, hitTransform[0], hitTransform[1], 0, 2, maxDecalsPerChar);

			vector originChar = ownerChar.GetOrigin();
			float farClip = ablSettings.Get("farClip").ToFloat();

			if (vector.Distance(playerTransform[3], originChar) < 3)
			{
				//Print("Applying Decals on Player Weapon");
				int maxDecalsPlayerWeapon = ablSettings.Get("maxDecalsPlayerWeapon").ToInt();

				float nearClip = ablSettings.Get("nearClip").ToFloat();
				ManageDecalStack(currentPlayerDecals, currentPlayer, hitTransform[0], hitTransform[1], nearClip, farClip, maxDecalsPlayerWeapon);
				Print("________________________");
			}
		}
	}

	
	
	
	void ManageDecalStack(array<ref DecalWrapper> stack, IEntity owner, vector hitPosition, vector hitDirection, float nearClip, float farClip, int maxDecals)
	{
		int materialColor = Color.FromRGBA(16, 0, 0,255).PackToInt();		//move this away
		
		auto param = new TraceParam();
  		param.Start = hitPosition;
  		param.End = hitPosition + hitDirection * farClip;
  		param.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
  		param.Exclude = owner;
		float intersectionDistance = worldTmp.TraceMove(param, NULL) * farClip;
		vector intersectionPosition = hitPosition + (hitDirection * intersectionDistance);
		
		ablSettings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);
		float diffOriginX = ablSettings.Get("diffOriginX").ToFloat();
		float diffOriginY = ablSettings.Get("diffOriginY").ToFloat();
		float diffOriginZ = ablSettings.Get("diffOriginZ").ToFloat();
		
		float decalAngle = ablSettings.Get("decalAngle").ToFloat();
		bool debugSpheres = ablSettings.Get("debugSpheres").ToInt();
		
		
		
		float rotation = Math.RandomFloatInclusive(-decalAngle, decalAngle);

		//ResourceName tempMaterial = "{82129FA9BA80D8F4}materials/WeaponBloodSecondTry.emat";
		ResourceName tempMaterial = "{098960A4823D679F}materials/weapon_splatter/WeaponBlood.emat";
		
		int count = stack.Count();
		if (count >= maxDecals)
		{
			int index = Math.RandomIntInclusive(0, stack.Count() - 1);
			//Print("Removing element " + index);
			DecalWrapper tmpWrapper = stack.Get(index);
			Decal tmpDecal = tmpWrapper.wrappedDecal;
			if (tmpDecal)
			{
				worldTmp.RemoveDecal(tmpDecal);
				stack.Remove(index);
			}

		}
		
		
		count = stack.Count();
		if (count < maxDecals)
		{
			
			vector leftHandTransform[4];
			int nodeLeftHand = 2089750091;
			owner.GetBoneMatrix(nodeLeftHand, leftHandTransform);

			
			vector tmpTransformHand = leftHandTransform[3];
			tmpTransformHand[0] = tmpTransformHand[0] + diffOriginX;
			tmpTransformHand[1] = tmpTransformHand[1] + diffOriginY;
			tmpTransformHand[2] = tmpTransformHand[2] + diffOriginZ;
			
			vector tmpOrigin = owner.CoordToParent(tmpTransformHand);
			vector tmpProjection = tmpOrigin;

			DecalWrapper newTmpWrapperLeft = DecalWrapper(worldTmp.CreateDecal(owner, tmpOrigin, tmpProjection, nearClip, farClip, rotation, 1, 1, tempMaterial, -1, materialColor));
			stack.Insert(newTmpWrapperLeft);
			if(debugSpheres)
				MCF_Debug.DrawSphereAtPos(tmpOrigin, COLOR_RED);

		}

		
	}
	
	
	//------------------------------------------------------------------------------------------------

	
	static void CleanWeapon()
	{
		
		//todo spherecast and get near decals.
		//Print(previousPlayerWeaponDecal);
		Print(currentPlayerDecals.Count());
		
		

		int count = currentPlayerDecals.Count();
		
		foreach(DecalWrapper decWrapper : currentPlayerDecals)
		{
			Decal tmpDecal = decWrapper.wrappedDecal;
			
			if (tmpDecal)
			{
				Print("Removing decal: " + tmpDecal);
				SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
				IEntity currentPlayer = m_playerController.GetMainEntity();
				SCR_CharacterControllerComponent.Cast(currentPlayer.FindComponent(SCR_CharacterControllerComponent)).SetInspectionMode(true);
				GetGame().GetWorld().RemoveDecal(tmpDecal);		//doesn't automatically destroy the pointer

			}
		}
		
		currentPlayerDecals.Clear();

	}
	
	


	

}





class TestClass
{

	// generate perlin noise 
	
	// write it to edds file... ttttttthat we don't have any idea how to do it 
	
	//  register it
		//class GeneratedResources
	//{
	//	proto bool RegisterResource(string absPath, out ResourceName resourceName);
	//
	//	private void GeneratedResources();
	//	private void ~GeneratedResources();
	//}

	// read it
	
	/*
		// ! saves perlin in an image for debug purposes
	void PerlinDebug()
	{
			string filePath = "d:\\test.dds";
			ref array<int> data = new array<int>;
		
			const int WIDTH = 1024;
			const int HEIGHT = 1024;
		
			for (int y = 0; y < HEIGHT; y++) for (int x = 0; x < WIDTH; x++)
			{
				int count = x * y;
			
				float perlinVal = Math.PerlinNoise(x/m_fPerlinFrequency, y/m_fPerlinFrequency);
				//Print(perlinVal);
					
				int pixel = ARGB(255, perlinVal * 255, perlinVal * 255, perlinVal * 255 );
				data.Insert(pixel);
			}

			// save dds to file
			if (TexTools.SaveImageData(filePath, WIDTH, HEIGHT, data) == false)
			{
				//Print("Can't save image", LogLevel.ERROR);
				return;
			}
	}
	*/		
	
	//FUCK YOU FOUND YOU FUCK YOU

	//delete it... jesus what a shitshow
}





class DecalWrapper
{
	Decal wrappedDecal;
	
	
	void DecalWrapper(Decal d)
	{
		wrappedDecal = d;
	
	}

}