modded class SCR_CharacterControllerComponent : CharacterControllerComponent
{
	BS_AnimatedBloodManager animatedBloodManager;
	SCR_CharacterDamageManagerComponent characterDamageManagerComponent;

	override void OnDeath(IEntity instigatorEntity, notnull Instigator instigator)
	{
		super.OnDeath(instigatorEntity, instigator);

		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimatedBloodManager.Cast(GetGame().SpawnEntity(BS_AnimatedBloodManager, GetGame().GetWorld(), null));

		// characterDamageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(GetOwner().FindComponent(SCR_CharacterDamageManagerComponent));

		// if (!characterDamageManagerComponent)
		//	return;

		// bloodpools

		// remove droplets.
		GetGame().GetCallqueue().Remove(animatedBloodManager.SpawnDroplets);
		GetGame().GetCallqueue().Remove(animatedBloodManager.SpawnBloodTrail);

		// Remove trailing
		// characterDamageManagerComponent.DisableBloodTrail();
	}
}