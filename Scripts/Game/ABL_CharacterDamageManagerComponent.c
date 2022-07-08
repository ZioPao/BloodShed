modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	ref map<string, string> ablSettings;
	
	const string ABL_FileNameJson = "ABL_Settings.json";
	const string ABL_MOD_ID = "59951797A291CA02";				//it's probably possible to get this in a better way but ok
	const ResourceName weaponSplatterMaterial = "{098960A4823D679F}materials/weapon_splatter/WeaponBlood.emat";

	IEntity currentCharacter;
	bool alreadyDestroyed = false;
	float timerBetweenSplatters; 
	
	
	World worldTmp;

	
	ref static array<ref DecalWrapper> currentPlayerDecals;
	ref array<ref DecalWrapper> currentCharacterDecals;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		currentCharacter = owner;
		auto world = owner.GetWorld();
		
		
		currentCharacterDecals = new ref array<ref DecalWrapper>();
		
		if (!currentPlayerDecals)
			currentPlayerDecals = new array<ref DecalWrapper>();
		
		worldTmp = GetGame().GetWorld();
		
		//TODO THIS IS WRONG! WE CAN'T PUT IT HERE!

		////////////////////////////////////////////////////////////////////////////////////////////////
		//Settings initialization stuff 
		MCF_SettingsManager ABL_mcfSettingsManager = MCF_SettingsManager.GetInstance();
		OrderedVariablesMap ablVariablesMap = new OrderedVariablesMap();
				
		ablVariablesMap.Set("waitTimeBetweenFrames", new VariableInfo("Wait Times between frames (in seconds)", "0.033", EFilterType.TYPE_FLOAT));
		
		
		
		ablVariablesMap.Set("bloodpoolMinimumAlphaMulChange", new VariableInfo("Minimum limit for random change of bloodpool alpha multiplier", "0.0002", EFilterType.TYPE_FLOAT));
		ablVariablesMap.Set("bloodpoolMaximumAlphaMulChange", new VariableInfo("Max upper limit for random change of bloodpool alpha multiplier", "0.03", EFilterType.TYPE_FLOAT));
			
		ablVariablesMap.Set("wallsplatterMinimumAlphaMulChange", new VariableInfo("Minimum limit for random change of wall splatter alpha multiplier", "0.0001", EFilterType.TYPE_FLOAT));
		ablVariablesMap.Set("wallsplatterMaximumAlphaMulChange", new VariableInfo("Max upper limit for random change of wall splatter alpha multiplier", "0.02", EFilterType.TYPE_FLOAT));
		
		ablVariablesMap.Set("wallsplatterMinimumAlphaTestChange", new VariableInfo("Minimum limit for random change of wall splatter alpha test", "0.0001", EFilterType.TYPE_FLOAT));
		ablVariablesMap.Set("wallsplatterMaximumAlphaTestChange", new VariableInfo("Max upper limit for random change of wall splatter alpha test", "0.02", EFilterType.TYPE_FLOAT));
	
			
		ablVariablesMap.Set("maxAlphaMul", new VariableInfo("Max Alpha Multiplier limit", "5", EFilterType.TYPE_FLOAT));			//max 5
		ablVariablesMap.Set("minAlphaTest", new VariableInfo("Minimum Alpha Test", "0.1", EFilterType.TYPE_FLOAT));

	
			
		ablVariablesMap.Set("maxDecalsPerChar", new VariableInfo("Max Decals per Character", "2", EFilterType.TYPE_INT));
		ablVariablesMap.Set("maxDecalsPlayerWeapon", new VariableInfo("Max Decals for Player Weapon", "6", EFilterType.TYPE_INT));
		//ablVariablesMap.Set("debugSpheres", new VariableInfo("Debug Spheres", "0"));
			
		ablVariablesMap.Set("bloodpoolSize", new VariableInfo("Bloodpol Size", "1.5", EFilterType.TYPE_FLOAT));
		ablVariablesMap.Set("wallsplatterSize", new VariableInfo("Wallsplatter Size", "1", EFilterType.TYPE_FLOAT));
			
			

		//ablVariablesMap.Set("diffOriginX", new VariableInfo("Diff Origin X (TEST)", "0"));
		//ablVariablesMap.Set("diffOriginY", new VariableInfo("Diff Origin Y (TEST)", "0"));
			//ablVariablesMap.Set("diffOriginZ", new VariableInfo("Diff Origin Z (TEST)", "0"));
			//ablVariablesMap.Set("decalAngle", new VariableInfo("Decal Angle", "0"));
			//ablVariablesMap.Set("nearClip", new VariableInfo("Near Clip (TEST)", "0"));
			//ablVariablesMap.Set("farClip", new VariableInfo("Far Clip (TEST)", "2"));
			
			
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
			
		
		
		if (MCF_SettingsManager.IsInitialized())
		{
			MCF_SettingsManager ABL_mcfSettingsManager = MCF_SettingsManager.GetInstance();
			ablSettings = ABL_mcfSettingsManager.GetModSettings(ABL_MOD_ID);
		
			
			//Setup AnimatedDecalManager
			ABL_AnimatedDecalManager animatedDecalManager;		
			animatedDecalManager = ABL_AnimatedDecalManager.GetInstance();		
			if (!animatedDecalManager)
				animatedDecalManager = ABL_AnimatedDecalManager.Cast(GetGame().SpawnEntity(ABL_AnimatedDecalManager, GetGame().GetWorld(), null));
				
			
			ablSettings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);
	
			
			//Useless
			vector _tmpVec[4];
			int _correctBoneId;
			//Useless
			
			int correctNodeId;
			int colliderDescriptorIndex = pHitZone.GetColliderDescriptorIndex(colliderID);
			pHitZone.TryGetColliderDescription(currentCharacter, colliderDescriptorIndex, _tmpVec, _correctBoneId, correctNodeId);
			
	
			
			if (hitTransform[0].Length() != 0)
			{
				
				if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
				{
					GetGame().GetCallqueue().CallLater(animatedDecalManager.StartNewAnimation, 2000, false, currentCharacter, hitTransform[0], hitTransform[1], EDecalType.BLOODPOOL, false, 1.5, correctNodeId);
					
					
					// call another method to manage particles 
					
					alreadyDestroyed = true;		//only once
				}
				else if (damage > 20.0)
				{
					//todo add a timer to prevent more than 1 splatter on the wall 
					animatedDecalManager.StartNewAnimation(currentCharacter,  hitTransform[0],  hitTransform[1], EDecalType.WALLSPLATTER, false, 0.0, correctNodeId);
					

					//spawns particles 
					
					
					
				}
			
	
				//GenerateWeaponSplatters(currentCharacter, ablSettings);
				//if (Math.RandomInt(0,21) > 10)		//todo make it customizable
				//	animatedDecalManager.SpawnSingleFrame(currentCharacter, worldTmp, hitTransform[0], hitTransform[1]);
	
				
			}
		}
	}
	

	
	void GenerateBloodParticleEmitter(vector position[3])
	{
			
		//SCR_ParticleEmitter particleEmitter = SCR_ParticleAPI.PlayOnObjectPTC(GetOwner(), m_sBleedingParticle, vector.Zero, vector.Zero, boneNode);
		//SCR_ParticleAPI.LerpAllEmitters(particleEmitter, bleedingRate * m_fBleedingParticleRateScale, EmitterParam.BIRTH_RATE);
		
		//if (!m_mBleedingParticles)
		//	m_mBleedingParticles = new map<HitZone, SCR_ParticleEmitter>;
		
		//m_mBleedingParticles.Insert(hitZone, particleEmitter);
	
	}
	
	
	void GenerateWeaponSplatters(IEntity currentChar, map<string,string> settings)
	{
		
		// Settings
		float farClip = ablSettings.Get("farClip").ToFloat();
		float nearClip = ablSettings.Get("nearClip").ToFloat();
		int maxDecalsPlayerWeapon = ablSettings.Get("maxDecalsPlayerWeapon").ToInt();	
		bool debugSpheres = 0;			//settings.Get("debugSpheres").ToInt();
		
		// Other characters 
		int maxDecalsPerChar = ablSettings.Get("maxDecalsPerChar").ToInt();
		ManageWeaponDecalsStack(currentChar, currentCharacterDecals, 0, 2, maxDecalsPerChar);

		// Player Weapon
		PlayerManager pMan = GetGame().GetPlayerManager();
		SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		IEntity currentPlayer = m_playerController.GetMainEntity();
		vector playerTransform[4];
		currentPlayer.GetTransform(playerTransform);		
			

		
		
		vector originCurrentCharacter = currentChar.GetOrigin();

		if (vector.Distance(playerTransform[3], originCurrentCharacter) < 3)
			ManageWeaponDecalsStack(currentPlayer, currentPlayerDecals, nearClip, farClip, maxDecalsPlayerWeapon, debugSpheres);
		
	
	}
	


	
	
	
	
	
	
	void ManageWeaponDecalsStack(IEntity owner, array<ref DecalWrapper> stack, float nearClip, float farClip, int maxDecals, bool debugSpheres = false)
	{
		int materialColor = Color.FromRGBA(16, 0, 0,255).PackToInt();		//move this away
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
		
		// Tries to generate a decal
		count = stack.Count();
		if (count < maxDecals)
		{
			
			vector leftHandTransform[4];
			int nodeLeftHand = 2089750091;
			owner.GetBoneMatrix(nodeLeftHand, leftHandTransform);

			
			vector tmpTransformHand = leftHandTransform[3];
			tmpTransformHand[0] = tmpTransformHand[0]; //+ diffOriginX;
			tmpTransformHand[1] = tmpTransformHand[1]; //+ diffOriginY;
			tmpTransformHand[2] = tmpTransformHand[2]; //+ diffOriginZ;
			
			vector origin = owner.CoordToParent(tmpTransformHand);
			vector projection = origin;

			DecalWrapper newTmpWrapperLeft = DecalWrapper(worldTmp.CreateDecal(owner, origin, projection, nearClip, farClip, 0, 1, 1, weaponSplatterMaterial, -1, materialColor));
			stack.Insert(newTmpWrapperLeft);
			if(debugSpheres)
				MCF_Debug.DrawSphereAtPos(origin, COLOR_RED);

		}

		
	}
	
	
	//------------------------------------------------------------------------------------------------

	
	static void CleanWeapon()
	{
		
		//todo spherecast and get near decals.
		//Print(previousPlayerWeaponDecal);
		//Print(currentPlayerDecals.Count());
		
		

		int count = currentPlayerDecals.Count();
		
		foreach(DecalWrapper decWrapper : currentPlayerDecals)
		{
			Decal tmpDecal = decWrapper.wrappedDecal;
			
			if (tmpDecal)
			{
				//Print("Removing decal: " + tmpDecal);
				SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
				IEntity currentPlayer = m_playerController.GetMainEntity();
				SCR_CharacterControllerComponent.Cast(currentPlayer.FindComponent(SCR_CharacterControllerComponent)).SetInspectionMode(true);
				GetGame().GetWorld().RemoveDecal(tmpDecal);		//doesn't automatically destroy the pointer

			}
		}
		
		currentPlayerDecals.Clear();

	}
	
	
	
	override void CreateBleedingParticleEffect(notnull HitZone hitZone, float bleedingRate, int colliderDescriptorIndex)
	{
		// Play Bleeding particle
		if (m_sBleedingParticle.IsEmpty())
			return;
		
		RemoveBleedingParticleEffect(hitZone);
		
		if (bleedingRate == 0 || m_fBleedingParticleRateScale == 0)
			return;
		
		// TODO: Blood traces on ground that should be left regardless of clothing, perhaps just delayed
		SCR_CharacterHitZone characterHitZone = SCR_CharacterHitZone.Cast(hitZone);
		
		//Let's just disable this.
		//if (characterHitZone.IsCovered())
		//	return;
		
		// Get bone node
		vector transform[4];
		int boneIndex;
		int boneNode;
		if (!hitZone.TryGetColliderDescription(GetOwner(), colliderDescriptorIndex, transform, boneIndex, boneNode))
			return;
		
		SCR_ParticleEmitter particleEmitter = SCR_ParticleAPI.PlayOnObjectPTC(GetOwner(), m_sBleedingParticle, vector.Zero, vector.Zero, boneNode);
		SCR_ParticleAPI.LerpAllEmitters(particleEmitter, bleedingRate * m_fBleedingParticleRateScale, EmitterParam.BIRTH_RATE);
		
		if (!m_mBleedingParticles)
			m_mBleedingParticles = new map<HitZone, SCR_ParticleEmitter>;
		
		m_mBleedingParticles.Insert(hitZone, particleEmitter);
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