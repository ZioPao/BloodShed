modded class SCR_PlayerController : PlayerController
{

	override void UpdateLocalPlayerController()
	{
		super.UpdateLocalPlayerController();
		
		GetGame().GetInputManager().AddActionListener("CleanWeapon", EActionTrigger.DOWN, CleanWeaponCallback);

	
	}
	
	
	void CleanWeaponCallback()
	{
		Print("Squeeky clean");
		BS_AnimateBloodManager.CleanWeapon();
	}


}