modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{

	IEntity ownerChar;
	bool alreadyDestroyed = false;
	World worldTmp;

	const int MAX_DECALS_PER_STACK = 2;
	
	ref static SCR_Stack<DecalWrapper> currentPlayerDecals;
	ref SCR_Stack<DecalWrapper> currentCharacterDecals;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		ownerChar = owner;
		auto world = owner.GetWorld();
		
		
		currentCharacterDecals = new ref SCR_Stack<DecalWrapper>();
		
		if (!currentPlayerDecals)
			currentPlayerDecals = new SCR_Stack<DecalWrapper>();
		
		worldTmp = GetGame().GetWorld();

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

		
		if ( hitTransform[0].Length() != 0)
		{
		
			if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
			{
				//Print("Start blood");
				GetGame().GetCallqueue().CallLater(tempManager.StartNewAnimation, 2000, false, ownerChar, hitTransform[0], hitTransform[1], EDecalType.BLOODPOOL, true, 1.5, correctNodeId);
	
				//tempManager.StartNewAnimation(ownerChar, hitTransform[0],  hitTransform[1], EDecalType.BLOODPOOL, true);
				alreadyDestroyed = true;		//only once
			}
			else if (damage > 20.0)
				tempManager.StartNewAnimation(ownerChar,  hitTransform[0],  hitTransform[1], EDecalType.GENERIC_SPLATTER, false, 0.0, correctNodeId);

			// Manages splatters on weapons 
			ResourceName tempMaterial = "{098960A4823D679F}materials/WeaponBlood.emat";
			PlayerManager pMan = GetGame().GetPlayerManager();
			SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			IEntity currentPlayer = m_playerController.GetMainEntity();
			vector playerTransform[4];

			currentPlayer.GetTransform(playerTransform);
			ManageDecalStack(currentCharacterDecals, ownerChar, hitTransform[0], -hitTransform[1], MAX_DECALS_PER_STACK, 2);

			vector originChar = ownerChar.GetOrigin();
			
			//reset it
			if (vector.Distance(playerTransform[3], originChar) < 100)
			{
				//Print("Test");
				float farClipPlayerWeaponDecal = vector.Distance(playerTransform[3], originChar);
				
				//Print(testVec);
				//Print(originPlayer);
				vector normal = playerTransform[0];		//1st one is the normal I guess?
				ManageDecalStack(currentPlayerDecals, currentPlayer, hitTransform[0], -hitTransform[1], 3, 6, false);
			}
		}
	}

	
	
	
	void ManageDecalStack(SCR_Stack<DecalWrapper> stack, IEntity owner, vector orig, vector direct, float farClip, int maxDecals, bool shouldPop = true)
	{
		int materialColor = Color.FromRGBA(16, 0, 0,255).PackToInt();		//move this away

		vector projection;
		ABL_AnimatedDecalManager.GetSurfaceIntersection(owner, worldTmp, orig, direct, 5, TraceFlags.ENTS, projection);
		
		
		
		if (shouldPop)
		{
			if (stack.Count() > maxDecals)
			{
				DecalWrapper tmpWrapper = stack.Pop();
				Decal tmpDecal = tmpWrapper.wrappedDecal;
				if (tmpDecal)
					worldTmp.RemoveDecal(tmpDecal);
				
	
			}
		}
		if (stack.Count() < maxDecals)
		{
			Print("Creating splatter");
			DecalWrapper newTmpWrapper = DecalWrapper(worldTmp.CreateDecal(owner, orig, projection, 0, farClip, 0, 1, 1, "{098960A4823D679F}materials/WeaponBlood.emat", -1, materialColor));
			stack.Push(newTmpWrapper);
		}

		
	}
	
	
	

	
	
	static void CleanWeapon()
	{
		
		//todo spherecast and get near decals.
		//Print(previousPlayerWeaponDecal);
		Print(currentPlayerDecals.Count());
		for (int i = 0; i < currentPlayerDecals.Count(); i++)
		{
		
			DecalWrapper decWrapper = currentPlayerDecals.Pop();
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