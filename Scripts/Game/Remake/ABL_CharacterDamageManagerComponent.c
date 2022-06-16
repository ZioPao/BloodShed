modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{

	IEntity ownerChar;
	bool alreadyDestroyed = false;


	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		ownerChar = owner;
		auto world = owner.GetWorld();

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

		if (!tempManager)
			tempManager = ABL_AnimatedDecalManager.Cast(GetGame().SpawnEntity(ABL_AnimatedDecalManager, GetGame().GetWorld(), null));

		
		if ( hitTransform[0].Length() != 0)
		{
		
			if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
			{
				Print("Start blood");
				GetGame().GetCallqueue().CallLater(tempManager.StartNewAnimation, 600, false, ownerChar, hitTransform[0], hitTransform[1], EDecalType.BLOODPOOL, true);
	
				//tempManager.StartNewAnimation(ownerChar, hitTransform[0],  hitTransform[1], EDecalType.BLOODPOOL, true);
				alreadyDestroyed = true;		//only once
			}
			else if (damage > 20.0)
				tempManager.StartNewAnimation(ownerChar,  hitTransform[0],  hitTransform[1], EDecalType.GENERIC_SPLATTER, false);

		
		}
		
		
		
	   
	}

	override void OnFrame(IEntity owner, float timeSlice)
	{
		super.OnFrame(owner, timeSlice);
		//m_bleedBehavior.OnFrame();
		//m_splatterBehavior.OnFrame(owner, timeSlice);
	}
	

	

}