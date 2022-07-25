modded class SCR_CharacterControllerComponent : CharacterControllerComponent
{
	BS_AnimatedBloodManager animatedBloodManager;		
	SCR_CharacterDamageManagerComponent characterDamageManagerComponent;
	
	override void OnDeath(IEntity instigator)
	{
		super.OnDeath(instigator);
		
				
		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();		
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimatedBloodManager.Cast(GetGame().SpawnEntity(BS_AnimatedBloodManager, GetGame().GetWorld(), null));
		
		//characterDamageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(GetOwner().FindComponent(SCR_CharacterDamageManagerComponent));
		
		//if (!characterDamageManagerComponent)
		//	return;
		
		
		
		//bloodpools 

		
		// remove droplets. 
		GetGame().GetCallqueue().Remove(animatedBloodManager.SpawnDroplets);
		
		//Remove trailing
		characterDamageManagerComponent.DisableBloodTrail();

	}

}