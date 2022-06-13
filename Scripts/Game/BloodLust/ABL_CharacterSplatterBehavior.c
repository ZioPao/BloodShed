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
	const int MAX_ANIMATED_DECALS = 10;
	ref map<int, Decal> decalsSpawned;
	ref map<int, int> decalsFramesOfAnimation;

	
	
	
	override void OnInit(
		IEntity owner,
		World world,
		SCR_CharacterDamageManagerComponent damageManagerComponent)
	{
		
		super.OnInit(owner, world, damageManagerComponent);
		decalsSpawned = new map<int, Decal>();
		decalsFramesOfAnimation = new map<int, int>();
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
		

		hitPosition = hitTransform[0];
		hitDirection = hitTransform[1];
		hitDamage = damage;
		//vector hitNormal = hitTransform[2];
		
			
		//Print("OnDamage");
		if (decalsSpawned.Count() < MAX_ANIMATED_DECALS)
		{
			//isCurrentlySpawning = true;
			Print("Spawning!");
			Print(hitDirection);
			SpawnAnimatedBloodSplatterFirstFrame();
			GetGame().GetCallqueue().CallLater(SpawnAnimatedBloodSplatter, 10, true);
		}

	
			
			
		
		

	}
	
	ref array<ResourceName> materials = {"{A9E0DD7726DB0B7B}test2/0.emat","{5DE89AEF2B06630F}test2/1.emat","{0300B3AC948BED00}test2/2.emat",
		"{F708F43499568574}test2/3.emat","{BED0E12BEB90F11E}test2/4.emat","{4AD8A6B3E64D996A}test2/5.emat","{14308FF059C01765}test2/6.emat",
		"{E038C868541D7F11}test2/7.emat","{8780A5CEBC4CFFB1}test2/8.emat","{7388E256B19197C5}test2/9.emat","{08FE0005075EBCEC}test2/10.emat",
		"{FCF6479D0A83D498}test2/11.emat","{A21E6EDEB50E5A97}test2/12.emat","{56162946B8D332E3}test2/13.emat","{1FCE3C59CA154689}test2/14.emat",
		"{EBC67BC1C7C82EFD}test2/15.emat","{B52E52827845A0F2}test2/16.emat","{4126151A7598C886}test2/17.emat","{269E78BC9DC94826}test2/18.emat",
		"{D2963F2490142052}test2/19.emat","{025B5048B14E4F6B}test2/20.emat","{F65317D0BC93271F}test2/21.emat","{A8BB3E93031EA910}test2/22.emat",
		"{5CB3790B0EC3C164}test2/23.emat","{156B6C147C05B50E}test2/24.emat","{E1632B8C71D8DD7A}test2/25.emat","{BF8B02CFCE555375}test2/26.emat",
		"{4B834557C3883B01}test2/27.emat","{2C3B28F12BD9BBA1}test2/28.emat","{D8336F692604D3D5}test2/29.emat","{C597C0D544180C67}test2/30.emat",
		"{319F874D49C56413}test2/31.emat","{6F77AE0EF648EA1C}test2/32.emat","{9B7FE996FB958268}test2/33.emat","{D2A7FC898953F602}test2/34.emat",
		"{26AFBB11848E9E76}test2/35.emat","{784792523B031079}test2/36.emat","{8C4FD5CA36DE780D}test2/37.emat","{EBF7B86CDE8FF8AD}test2/38.emat",
		"{1FFFFFF4D35290D9}test2/39.emat","{1711F0D3DD6FA865}test2/40.emat","{E319B74BD0B2C011}test2/41.emat","{BDF19E086F3F4E1E}test2/42.emat",
		"{49F9D99062E2266A}test2/43.emat","{0021CC8F10245200}test2/44.emat","{F4298B171DF93A74}test2/45.emat","{AAC1A254A274B47B}test2/46.emat",
		"{5EC9E5CCAFA9DC0F}test2/47.emat","{3971886A47F85CAF}test2/48.emat","{CD79CFF24A2534DB}test2/49.emat","{D0DD604E2839EB69}test2/50.emat",
		"{24D527D625E4831D}test2/51.emat","{7A3D0E959A690D12}test2/52.emat","{8E35490D97B46566}test2/53.emat","{C7ED5C12E572110C}test2/54.emat",
		"{33E51B8AE8AF7978}test2/55.emat","{6D0D32C95722F777}test2/56.emat","{990575515AFF9F03}test2/57.emat","{FEBD18F7B2AE1FA3}test2/58.emat",
		"{0AB55F6FBF7377D7}test2/59.emat","{DA7830039E2918EE}test2/60.emat","{2E70779B93F4709A}test2/61.emat","{70985ED82C79FE95}test2/62.emat",
		"{8490194021A496E1}test2/63.emat"};
	
	
	
	
	
	void SpawnAnimatedBloodSplatter()
	{
		//todo this needs to be in a dedicated class separated from the character to prevent stopping from death 

		foreach(int index, Decal d : decalsSpawned)
		{
			//Print("Decal: " + index);
			int frameIndex = decalsFramesOfAnimation.Get(index);
			Print("Frame: " + frameIndex);
			


			
			if (frameIndex < MAX_FRAMES)
			{
				//updates animation frames for already spawned decals 
				if (d)
				{
					Print(d);
					m_world.RemoveDecal(d);
				}
				else
					Print("NO DECAL!!!");
				
				vector intersectionPosition;
				int materialColor = BL_Utilities.CalculateBloodColorFromDamage(hitDamage);
		
				// attempt ground splatter, using hitPosition as a "trigger"
				// attempt surface splatter, using the hitDirection as a "trigger"
				auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE, intersectionPosition);
				if (surfaceTraceParam.TraceEnt) // spawn splatter below character
				{
					//todo I really need to udnerstand how these values work.
					 decalsSpawned.Set(index, m_world.CreateDecal(surfaceTraceParam.TraceEnt, intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4), hitDirection, 0, BL_Constants.DECAL_FAR_PLANE, 0,  
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
		Print("First Frame");
		vector intersectionPosition;
		int materialColor = BL_Utilities.CalculateBloodColorFromDamage(hitDamage);
	
		auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(
			m_owner,
			m_world,
			hitPosition,
			hitDirection,
			BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE,
			intersectionPosition);
		
		
		if (surfaceTraceParam.TraceEnt) // spawn splatter on surface
		{
			Decal tmpDecal = m_world.CreateDecal(
				surfaceTraceParam.TraceEnt,
				intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4),
				hitDirection,
				0,
				BL_Constants.DECAL_FAR_PLANE,
				0,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				1.0, //Math.RandomFloat(MIN_DECAL_SIZE, MAX_DECAL_SIZE),
				1,
				materials[0],
				BL_Constants.DECAL_LIFETIME_SECS,
				materialColor);
			
					
			int index = decalsSpawned.Count();
			decalsSpawned.Insert(index, tmpDecal);
			decalsFramesOfAnimation.Insert(index, 0);		//first frame
		}
		
	}
	
	

	
	
	override void OnFrame(IEntity owner, float timeSlice)
	{
	}
	
	
	
	
	private void SpawnAnimatedBloodSplatterFromHit()
	{
	
		vector intersectionPosition;
		int materialColor = BL_Utilities.CalculateBloodColorFromDamage(hitDamage);

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