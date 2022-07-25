[ComponentEditorProps(category: "GameScripted/Test", description:"BS_BloodTrails", color: "0 0 255 255")]
class BS_BloodTrailsClass : ScriptComponentClass
{
};

class BS_BloodTrails : ScriptComponent
{	
	[Attribute("{AE248EE9E164EB4C}Assets/Decals/BloodDecal.emat", UIWidgets.ResourceNamePicker, desc: "Material for bloodtrail", params: "emat")]
	private ResourceName m_TrackMaterial;

	bool shouldBleed;
	
	
	
	ref array<ref BloodTrailInfo> m_TrackDecalsInfo;

	
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
		
		m_TrackDecalsInfo = new array<ref BloodTrailInfo>();
		m_TrackDecalsInfo.Resize(1);
		m_TrackDecalsInfo[0] = new BloodTrailInfo();


		
		SetEventMask(owner, EntityEvent.FRAME);

	}
	
	
	void ActivateBloodtrail(IEntity character)
	{
	
		vector useless;
		traceParam = BS_AnimatedBloodManager.GetSurfaceIntersection(character, GetGame().GetWorld(), character.GetOrigin(), Vector(0, -1, 0), 2, TraceFlags.WORLD | TraceFlags.ENTS, useless);

		
		
		SetEventMask(GetOwner(), EntityEvent.FRAME);
	}
	
	
	void DisableBloodtrail()
	{
		SetEventMask(GetOwner(), EntityEvent.DISABLED);

	
	}
	
	
	void UpdateTrack(IEntity owner)
	{
		
		
		//check if he's bleeding 
		BloodTrailInfo trackInfo = m_TrackDecalsInfo[0];

		
		SCR_CharacterDamageManagerComponent charDamageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(owner.FindComponent(SCR_CharacterDamageManagerComponent));
		SCR_CharacterControllerComponent charControllerComponent = SCR_CharacterControllerComponent.Cast(owner.FindComponent(SCR_CharacterControllerComponent));;

		
		float speed = charControllerComponent.GetDynamicSpeed();
		bool isBleeding = charDamageManagerComponent.IsDamagedOverTime(EDamageType.BLEEDING);
		Print(speed);
		shouldBleed = isBleeding && (speed > 0.55);
		
		
		
		
		
		
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
	
	
	float tempTimer = 0;
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		UpdateTrack(owner);

	}
		
	
}

class BloodTrailInfo : TrackDecalInfo
{
};