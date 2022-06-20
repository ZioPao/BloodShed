modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{

	IEntity ownerChar;
	bool alreadyDestroyed = false;

	
	
	static Decal previousPlayerWeaponDecal;
	ref SCR_Stack<DecalWrapper> currentCharacterDecals;
	//Decal currentWeaponDecal;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		ownerChar = owner;
		auto world = owner.GetWorld();
		
		
		currentCharacterDecals = new ref SCR_Stack<DecalWrapper>();

		//m_splatterBehavior = new ABL_Main;
		//m_splatterBehavior.OnInit(owner, world, this);

		//m_bleedBehavior = new BL_CharacterBleedBehavior;
		//m_bleedBehavior.OnInit(owner, world, this);
	}

	override void OnDamage(
			EDamageType type,
			float damage,
			HitZone pHitZone,
			IEntity instigator,
			inout vector hitTransform[3],
			float speed,
			int colliderID,
			int nodeID
	)
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
		
		
		//TNodeId idTmp = ownerChar.GetBoneIndex(boneNames[4]);
		//ownerChar.GetBoneMatrix(idTmp, testVec);
		
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
			
			
			
			//SPAWN SINGLE DECAL ON SPECIFIC POINT
		//	m_world.CreateDecal()

			ResourceName tempMaterial = "{098960A4823D679F}materials/WeaponBlood.emat";
			int materialColor = Color.FromRGBA(16, 0, 0,255).PackToInt();		//move this away
			World tempWorld = GetGame().GetWorld();
			
			
			
			PlayerManager pMan = GetGame().GetPlayerManager();
			SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			vector originPlayer[4];
			IEntity currentPlayer;
			
			currentPlayer = m_playerController.GetMainEntity();
			currentPlayer.GetTransform(originPlayer);
			
			
			
			if (currentCharacterDecals.Count() > 2)
			{
				Print("Popping older decals");
				DecalWrapper tmpCurrentCharDecalWrapper = currentCharacterDecals.Pop();
				Decal tmpCurrentCharDecal = tmpCurrentCharDecalWrapper.wrappedDecal;
				if (tmpCurrentCharDecal)
				{
					tempWorld.RemoveDecal(tmpCurrentCharDecal);
				
				}
			}
			
			DecalWrapper tmpWrapper = DecalWrapper(tempWorld.CreateDecal(ownerChar, hitTransform[0], hitTransform[0], 0, 2, 0, 1, 1, tempMaterial, -1, materialColor));
			currentCharacterDecals.Push(tmpWrapper);

			
			if (currentPlayer ==  ownerChar)
			{
				if (previousPlayerWeaponDecal)
				{
					Print("Removing previous decal on player weapon");
					tempWorld.RemoveDecal(previousPlayerWeaponDecal);

				}


			}

			previousPlayerWeaponDecal = tempWorld.CreateDecal(m_playerController.GetMainEntity(), hitTransform[0], originPlayer[0], 0, 2, 0, 1, 1, tempMaterial, -1, materialColor);

			
			
			
			
			
			
			
			//this should be cleaned to prevent the decals bug.

		}
		
		
		
	   
	}

	override void OnFrame(IEntity owner, float timeSlice)
	{
		super.OnFrame(owner, timeSlice);
		//m_bleedBehavior.OnFrame();
		//m_splatterBehavior.OnFrame(owner, timeSlice);
	}
	

	

}


class DecalWrapper
{
	Decal wrappedDecal;
	
	
	void DecalWrapper(Decal d)
	{
		wrappedDecal = d;
	
	}

}