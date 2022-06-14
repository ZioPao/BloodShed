modded class BL_CharacterSplatterBehavior
{
	private static const float MIN_DECAL_SIZE = 1;
	private static const float MAX_DECAL_SIZE = 1.25;
	private static const ref array<string> SPLATTER_MATERIAL_PATHS =
	{
		"{E1866216CEB08179}materials/splatters/1.emat",
		"{8E3E81D1390C727B}materials/splatters/2.emat",
		"{C7505DF437AA8B21}materials/splatters/3.emat",
		"{8E8848EB456CFF4B}materials/splatters/4.emat",
		"{7A800F7348B1973F}materials/splatters/5.emat",
		"{24682630F73C1930}materials/splatters/6.emat",
		"{D06061A8FAE17144}materials/splatters/7.emat",
	};

	private IEntity m_owner;
	private World m_world;
	private SCR_CharacterDamageManagerComponent m_damageManagerComponent;

	
	
	private float startTime;
	private float currentTime;
	private int currentIndex;
	private bool shouldSpawnBloodSplatter;
	private Decal currentDecal_1;
	private Decal currentDecal_2;
	
	
	private vector hitPosition;
	private vector hitDirection;
	private float hitDamage;
	
	
	const int MAX_FRAMES = 64;
	
	int materialColor;
	
	

	
	
	ref map<int, Decal> decalsSpawned;
	ref map<int, int> decalsFramesOfAnimation;
	ref map<int, float> decalsRotation;

		
	static int currentlyAnimatedDecals;
	static int MAX_ANIMATED_DECALS = 15;
	
	
	override void OnInit(
		IEntity owner,
		World world,
		SCR_CharacterDamageManagerComponent damageManagerComponent)
	{
		
		super.OnInit(owner, world, damageManagerComponent);
		decalsSpawned = new map<int, Decal>();
		decalsFramesOfAnimation = new map<int, int>();
		decalsRotation = new map<int, float>();
		isCurrentlySpawning = false;

	}
	
	
	bool isCurrentlySpawning = false;
	

	override void OnDamage(
			EDamageType type,
			float damage,
			HitZone pHitZone,
			IEntity instigator,
			inout vector hitTransform[3],
			float speed,
			int colliderID,
			int nodeID)
	{
		
		materialColor = Color.FromRGBA(128, 0, 0,255).PackToInt();		//move this away
		hitPosition = hitTransform[0];
		hitDirection = hitTransform[1];
		hitDamage = damage;
		//vector hitNormal = hitTransform[2];
		
			
		//Print("OnDamage");
		if (decalsSpawned.Count() < MAX_ANIMATED_DECALS)
		{
			
			//Print(decalsSpawned.Count());
			//currentlyAnimatedDecals++;
			//isCurrentlySpawning = true;
			//Print("Spawning!");
			//Print(hitDirection);
			SpawnAnimatedBloodSplatterFirstFrame();
			GetGame().GetCallqueue().CallLater(SpawnAnimatedBloodSplatter, 100, true);
		}

	
			
			
		
		

	}
	
	ref array<ResourceName> materials = {"{C7ADE32E13BAE5F3}test3/materials/0.emat","{1FFD03D5B7529B65}test3/materials/1.emat","{41152A9608DF156A}test3/materials/2.emat",
		"{B51D6D0E05027D1E}test3/materials/3.emat","{FCC5781177C40974}test3/materials/4.emat","{08CD3F897A196100}test3/materials/5.emat","{562516CAC594EF0F}test3/materials/6.emat",
		"{A22D5152C849877B}test3/materials/7.emat","{C5953CF4201807DB}test3/materials/8.emat","{319D7B6C2DC56FAF}test3/materials/9.emat","{4283FB5BEA1E9AE5}test3/materials/10.emat",
		"{B68BBCC3E7C3F291}test3/materials/11.emat","{E8639580584E7C9E}test3/materials/12.emat","{1C6BD218559314EA}test3/materials/13.emat","{55B3C70727556080}test3/materials/14.emat",
		"{A1BB809F2A8808F4}test3/materials/15.emat","{FF53A9DC950586FB}test3/materials/16.emat","{0B5BEE4498D8EE8F}test3/materials/17.emat","{6CE383E270896E2F}test3/materials/18.emat",
		"{98EBC47A7D54065B}test3/materials/19.emat","{4826AB165C0E6962}test3/materials/20.emat","{BC2EEC8E51D30116}test3/materials/21.emat","{E2C6C5CDEE5E8F19}test3/materials/22.emat",
		"{16CE8255E383E76D}test3/materials/23.emat","{5F16974A91459307}test3/materials/24.emat","{AB1ED0D29C98FB73}test3/materials/25.emat","{F5F6F9912315757C}test3/materials/26.emat",
		"{01FEBE092EC81D08}test3/materials/27.emat","{6646D3AFC6999DA8}test3/materials/28.emat","{924E9437CB44F5DC}test3/materials/29.emat","{8FEA3B8BA9582A6E}test3/materials/30.emat",
		"{7BE27C13A485421A}test3/materials/31.emat","{250A55501B08CC15}test3/materials/32.emat","{D10212C816D5A461}test3/materials/33.emat","{98DA07D76413D00B}test3/materials/34.emat",
		"{6CD2404F69CEB87F}test3/materials/35.emat","{323A690CD6433670}test3/materials/36.emat","{C6322E94DB9E5E04}test3/materials/37.emat","{A18A433233CFDEA4}test3/materials/38.emat",
		"{558204AA3E12B6D0}test3/materials/39.emat","{5D6C0B8D302F8E6C}test3/materials/40.emat","{A9644C153DF2E618}test3/materials/41.emat","{F78C6556827F6817}test3/materials/42.emat",
		"{038422CE8FA20063}test3/materials/43.emat","{4A5C37D1FD647409}test3/materials/44.emat","{BE547049F0B91C7D}test3/materials/45.emat","{E0BC590A4F349272}test3/materials/46.emat"
		,"{14B41E9242E9FA06}test3/materials/47.emat","{730C7334AAB87AA6}test3/materials/48.emat","{870434ACA76512D2}test3/materials/49.emat","{9AA09B10C579CD60}test3/materials/50.emat",
		"{6EA8DC88C8A4A514}test3/materials/51.emat","{3040F5CB77292B1B}test3/materials/52.emat","{C448B2537AF4436F}test3/materials/53.emat","{8D90A74C08323705}test3/materials/54.emat",
		"{7998E0D405EF5F71}test3/materials/55.emat","{2770C997BA62D17E}test3/materials/56.emat","{D3788E0FB7BFB90A}test3/materials/57.emat","{B4C0E3A95FEE39AA}test3/materials/58.emat",
		"{40C8A431523351DE}test3/materials/59.emat","{9005CB5D73693EE7}test3/materials/60.emat","{640D8CC57EB45693}test3/materials/61.emat","{3AE5A586C139D89C}test3/materials/62.emat","{CEEDE21ECCE4B0E8}test3/materials/63.emat"};
	
	void SpawnAnimatedBloodSplatter()
	{
		//todo this needs to be in a dedicated class separated from the character to prevent stopping from death 

		foreach(int index, Decal d : decalsSpawned)
		{
			//Print("Decal: " + index);
			int frameIndex = decalsFramesOfAnimation.Get(index);
			//Print("Frame: " + frameIndex);
			


			
			if (frameIndex < MAX_FRAMES)
			{
				//updates animation frames for already spawned decals 
				if (d)
				{
					Print("Trying to delete a decal");
					m_world.RemoveDecal(d);
				}
				//else
				//	Print("NO DECAL!!!");
				
				vector intersectionPosition;
		
				// attempt ground splatter, using hitPosition as a "trigger"
				// attempt surface splatter, using the hitDirection as a "trigger"
				auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE, intersectionPosition);
				if (surfaceTraceParam.TraceEnt) // spawn splatter below character
				{
					//todo I really need to udnerstand how these values work.
					
					
					vector origin = intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4);
					//Print(origin);

					vector projection = hitDirection;
					//float decalRotation = decalsRotation.Get(index);
					 decalsSpawned.Set(index, m_world.CreateDecal(surfaceTraceParam.TraceEnt, origin , projection, 0, 2.0, 0,  
						1.0, 1, materials[frameIndex], BL_Constants.DECAL_LIFETIME_SECS, materialColor));
					frameIndex++;
					decalsFramesOfAnimation.Set(index, frameIndex);
				}	
			}
			else
			{
				// FINISHED ANIMATION
				decalsFramesOfAnimation.Remove(index);
				decalsSpawned.Remove(index);
				currentlyAnimatedDecals--;
				GetGame().GetCallqueue().Remove(SpawnAnimatedBloodSplatter);
				//isCurrentlySpawning = false;		//relase the lock
			}
			
			
			
			

			
		}
		

		/*
		// attempt surface splatter, using the hitDirection as a "trigger"
		auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE, intersectionPosition);
		if (surfaceTraceParam.TraceEnt) // spawn splatter below character
		{
			 m_world.CreateDecal(surfaceTraceParam.TraceEnt, intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4), hitDirection, 0, BL_Constants.DECAL_FAR_PLANE, 0,  
				1.0, 1, materials[currentIndex], BL_Constants.DECAL_LIFETIME_SECS, materialColor);
		}	
		*/

	}
	
	
	
	
	
	
	void SpawnAnimatedBloodSplatterFirstFrame()
	{
		//Print("First Frame");
		vector intersectionPosition;

		
		//Print("Tryint to Create surfaceTraceParam");
		//Print(m_owner);
		//Print(m_world);
		//Print(hitPosition);
		//Print(hitDirection);
		//Print("_____________________");
		auto surfaceTraceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE, intersectionPosition);
		
		if (!surfaceTraceParam)
			Print("Something wrong");

		if (surfaceTraceParam.TraceEnt) // spawn splatter on surface
		{
			
			Print("Starting spawn first frame");
			vector origin = intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4);
			vector projection = hitDirection;
			//float rotation = Math.RandomFloat(0, 45) * Math.DEG2RAD;
			
			// color must be set HERE
			
			Decal tmpDecal = m_world.CreateDecal(surfaceTraceParam.TraceEnt, origin, projection, 0, BL_Constants.DECAL_FAR_PLANE,
				0, 1.0, 1, materials[0],BL_Constants.DECAL_LIFETIME_SECS,  materialColor);
			
			Print("First frame spawned");
			
			int index = decalsSpawned.Count();
			decalsSpawned.Set(index, tmpDecal);
			//decalsRotation.Insert(index, rotation);
			decalsFramesOfAnimation.Set(index, 1);		//first frame already done
		}
		
	}
	
	

	private TraceParam GetSurfaceIntersection(IEntity owner,World world,vector origin,vector direction, float distance, out vector intersectionPosition)
	{
		auto param = new TraceParam();
  		param.Start = origin;
  		param.End = origin + direction * distance;
  		param.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
  		param.Exclude = owner;
		Print("Done in GetSurfaceIntersection, going to make TraceMove");
		float intersectionDistance = world.TraceMove(param, NULL) * distance;
		Print("Tracemove done, making stupid thing and then return");
		
		if (!intersectionDistance)
			Print("STOP!");
		
		
		intersectionPosition = origin + (direction * intersectionDistance);
		return param;
	}
	
	override void OnFrame(IEntity owner, float timeSlice)
	{
	}
	
	
	
	
	private void SpawnAnimatedBloodSplatterFromHit()
	{
	
		vector intersectionPosition;
		materialColor = BL_Utilities.CalculateBloodColorFromDamage(hitDamage);

		// attempt ground splatter
		auto groundTraceParam = BL_Utilities.GetSurfaceIntersection(
			m_owner,
			m_world,
			hitPosition,
			Vector(0, -1, 0),
			BL_Constants.GROUND_SPLATTER_INTERSECTION_DISTANCE,
			intersectionPosition
		);
		if (groundTraceParam.TraceEnt) // spawn splatter below character
		{
			currentDecal_1 = m_world.CreateDecal(
				groundTraceParam.TraceEnt,
				m_owner.GetOrigin() + Vector(0, BL_Constants.DECAL_FAR_PLANE / 4, 0),
				vector.Lerp(-groundTraceParam.TraceNorm, hitDirection, 0.5),
				0,
				BL_Constants.DECAL_FAR_PLANE,
				0,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				1.0, //Math.RandomFloat(MIN_DECAL_SIZE, MAX_DECAL_SIZE),
				1,
				materials[currentIndex],
				BL_Constants.DECAL_LIFETIME_SECS,
				materialColor
			);
		}
		
		
		
		// attempt surface splatter
		auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(
			m_owner,
			m_world,
			hitPosition,
			hitDirection,
			BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE,
			intersectionPosition
		);
		if (surfaceTraceParam.TraceEnt) // spawn splatter on surface
		{
			currentDecal_2 = m_world.CreateDecal(
				surfaceTraceParam.TraceEnt,
				intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4),
				hitDirection,
				0,
				BL_Constants.DECAL_FAR_PLANE,
				0,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				1.0, //Math.RandomFloat(MIN_DECAL_SIZE, MAX_DECAL_SIZE),
				1,
				materials[currentIndex],
				BL_Constants.DECAL_LIFETIME_SECS,
				materialColor
			);
		}

		

		startTime = currentTime;
	}
	
	

}