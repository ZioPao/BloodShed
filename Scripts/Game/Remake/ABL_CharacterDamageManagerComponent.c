modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{

	
	
	// 1) must be initialized one time 
	// 2) each char will relate to this.

	
	
	
	
	
	// INVOKERS 
	private ref ScriptInvoker m_onStateChanged = new ScriptInvoker();
	
	
	private ref ABL_Main m_splatterBehavior;

	//private ref BL_CharacterBleedBehavior m_bleedBehavior;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);

		auto world = owner.GetWorld();

		m_splatterBehavior = new ABL_Main;
		m_splatterBehavior.OnInit(owner, world, this);

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

		if (damage >= 20.0)
		{
			m_splatterBehavior.OnDamage(GetState(), damage, hitTransform);
			
			// SCR_CharacterDamageManagerComponent
			
			//SCR_CharacterDamageManagerComponent tmp = SCR_CharacterDamageManagerComponent.Cast(GetCharacter().FindComponent(SCR_CharacterDamageManagerComponent));
			
			//m_bleedBehavior.OnDamage(type, damage, pHitZone, instigator, hitTransform, speed, colliderID, nodeID);
		}
	}

	override void OnFrame(IEntity owner, float timeSlice)
	{
		super.OnFrame(owner, timeSlice);
		//m_bleedBehavior.OnFrame();
		//m_splatterBehavior.OnFrame(owner, timeSlice);
	}
	

	

}