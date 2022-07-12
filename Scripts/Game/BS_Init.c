modded class SCR_BaseGameMode : BaseGameMode
{
	

	override void StartGameMode()
	{

		super.StartGameMode();
					
		//Setup animatedBloodManager
		BS_AnimateBloodManager animatedBloodManager;		
		animatedBloodManager = BS_AnimateBloodManager.GetInstance();		
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimateBloodManager.Cast(GetGame().SpawnEntity(BS_AnimateBloodManager, GetGame().GetWorld(), null));
				

		
		
	}



};