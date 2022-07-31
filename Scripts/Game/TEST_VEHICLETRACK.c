modded class SCR_VehicleTrackDecal : ScriptComponent 
{
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		
		UpdateTrack(owner, 0);
		
	}
	
	override void UpdateTrack(IEntity owner, int wheelIdx)
	{

		TrackDecalInfo trackInfo = m_TrackDecalsInfo[wheelIdx];

		VehicleWheeledSimulation wheeledSimulation = VehicleWheeledSimulation.Cast(owner.FindComponent(VehicleWheeledSimulation));
		
		
		
		bool shouldAddTrackDecal = (wheeledSimulation.GetSpeedKmh() > 20);			//if this is true for too long it's gonna crash.... I guess? So we've gotta check if the player is moving
		
		if(!shouldAddTrackDecal)
		{
			if(trackInfo.m_Decal)
			{
				Print("No contact");
				trackInfo.Finalize(0.25);
			}
			return;
		}
		
		vector position = m_VehicleWheeledSimulation.WheelGetContactPosition(wheelIdx);
		vector normal = "0 -1 0";
		IEntity contactEntity = m_VehicleWheeledSimulation.WheelGetContactEntity(wheelIdx);
		
		if(!trackInfo.m_Decal)
		{
			if(trackInfo.m_bConnectToPrevious)
			{
				trackInfo.m_Decal = GetOwner().GetWorld().CreateTrackDecal(contactEntity, trackInfo.m_vLastTracePos, trackInfo.m_vLastTraceNormal, 0.25, 120.0, m_TrackMaterial, null, 1.0);
				trackInfo.m_bConnectToPrevious = false;
				Print("Connected");
			}
			else
			{
				trackInfo.m_Decal = GetOwner().GetWorld().CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_TrackMaterial, null, 0.0);
				Print("New");
			}
		}
		else if(vector.DistanceSq(trackInfo.m_vLastAxlePos, position) > 0.01)
		{
			trackInfo.m_vLastAxlePos = position;
			
			int validationEnum = trackInfo.m_Decal.CanAddToTrackDecal(contactEntity, m_TrackMaterial, position);
			
			switch(validationEnum)
			{
				case -1:
				Print("Track error");
				break;
				case 0: //Valid
				{
					trackInfo.m_fLength += vector.Distance(position, trackInfo.m_vLastTracePos);
					
					if(!trackInfo.m_Decal.AddPointToTrackDecal(position, normal, 1.0))
					{
						trackInfo.Finalize(0.0);
						Print("Finalized point");
					}
				}
				break;
				case 1: // Different entity
				{
					TrackDecal oldDecal = trackInfo.m_Decal;
					oldDecal.FinalizeTrackDecal(false, 0);
					
					trackInfo.m_Decal = GetOwner().GetWorld().CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_TrackMaterial, oldDecal, 1.0);
					trackInfo.m_bConnectToPrevious = false;
					Print("Diff ent");
				}
				break;
				case 2: // Too far from last point
				{
					trackInfo.Finalize(0.1);
					trackInfo.m_fLength = 0.0;
					trackInfo.m_Decal = GetOwner().GetWorld().CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_TrackMaterial, null, 0.0);
					trackInfo.m_bConnectToPrevious = false;
					Print("Too far");
				}
				break;
			}
		}
		
		trackInfo.m_vLastTracePos = position;
		trackInfo.m_vLastTraceNormal = normal;
	}


}