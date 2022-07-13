modded class SCR_BaseGameMode : BaseGameMode
{
	

	override void StartGameMode()
	{

		super.StartGameMode();
					
		//Setup animatedBloodManager
		BS_AnimatedBloodManager animatedBloodManager;		
		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();		
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimatedBloodManager.Cast(GetGame().SpawnEntity(BS_AnimatedBloodManager, GetGame().GetWorld(), null));
				

		
		
	}



};