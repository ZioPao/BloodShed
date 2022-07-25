[ComponentEditorProps(category: "GameScripted/Test", description:"BS_BloodTrails", color: "0 0 255 255")]
class BS_BloodTrailsClass : ScriptComponentClass
{
};

class BS_BloodTrails : ScriptComponent
{	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Material for bloodtrail", params: "emat")]
	private ResourceName m_BloodtrailMaterial;

	bool shouldBleed;
	
	ref BloodTrailInfo bloodTrailInfo;
	ref TraceParam traceParam;
	
	
	
	override void OnPostInit(IEntity owner)
	{
		// Don't run this component on console app
		if (System.IsConsoleApp())
		{
			Deactivate(owner);
			return;
		}
		
		SetEventMask(owner, EntityEvent.INIT);
	}
	
	//------------------------------------------------------------------------------------------------  
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		GenericEntity generic_entity = GenericEntity.Cast(owner);
		bloodTrailInfo = new BloodTrailInfo();


		
		shouldBleed = false;

	}
	
	
	void ActivateBloodtrail(IEntity character)
	{
	
		shouldBleed = true;
		
		vector useless;
		traceParam = BS_AnimatedBloodManager.GetSurfaceIntersection(character, GetGame().GetWorld(), character.GetOrigin(), Vector(0, -1, 0), 2, TraceFlags.WORLD | TraceFlags.ENTS, useless);

		
		
		SetEventMask(GetOwner(), EntityEvent.FRAME);
	}
	
	
	void DisableBloodtrail()
	{
		shouldBleed = false;
		SetEventMask(GetOwner(), EntityEvent.DISABLED);

	
	}
	
	
	void UpdateTrack(IEntity owner)
	{
		BloodTrailInfo trackInfo = bloodTrailInfo;
		World tmpWorld = GetGame().GetWorld();
		
		if(!shouldBleed)
		{
			if(trackInfo.m_Decal)
			{
				Print("No contact");
				trackInfo.Finalize(0.25);
			}
			return;
		}
		
		vector position;
		vector normal;
		IEntity contactEntity = traceParam.TraceEnt;
		
		position = owner.GetOrigin();
		normal = "0 -1 0";		//for now 	
			
		if(!trackInfo.m_Decal)
		{
			if(trackInfo.m_bConnectToPrevious)
			{
				trackInfo.m_Decal = tmpWorld.CreateTrackDecal(contactEntity, trackInfo.m_vLastTracePos, trackInfo.m_vLastTraceNormal, 0.25, 120.0, m_BloodtrailMaterial, null, 1.0);
				trackInfo.m_bConnectToPrevious = false;
				Print("Connected");
			}
			else
			{
				trackInfo.m_Decal = tmpWorld.CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_BloodtrailMaterial, null, 0.0);
				Print("New");
			}
		}
		else if(vector.DistanceSq(trackInfo.m_vLastAxlePos, position) > 0.01)
		{
			trackInfo.m_vLastAxlePos = position;
			
			int validationEnum = trackInfo.m_Decal.CanAddToTrackDecal(contactEntity, m_BloodtrailMaterial, position);
			
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
					
					trackInfo.m_Decal = tmpWorld.CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_BloodtrailMaterial, oldDecal, 1.0);
					trackInfo.m_bConnectToPrevious = false;
					Print("Diff ent");
				}
				break;
				case 2: // Too far from last point
				{
					trackInfo.Finalize(0.1);
					trackInfo.m_fLength = 0.0;
					trackInfo.m_Decal = tmpWorld.CreateTrackDecal(contactEntity, position, normal, 0.25, 120.0, m_BloodtrailMaterial, null, 0.0);
					trackInfo.m_bConnectToPrevious = false;
					Print("Too far");
				}
				break;
			}
		}
		
		trackInfo.m_vLastTracePos = position;
		trackInfo.m_vLastTraceNormal = normal;
	}
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		World world = GetGame().GetWorld();
		UpdateTrack(owner);
	}
		
	
}

class BloodTrailInfo : TrackDecalInfo
{
};