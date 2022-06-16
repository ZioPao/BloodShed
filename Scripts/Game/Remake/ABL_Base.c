class ABL_Main
{
	private static const float MIN_DECAL_SIZE = 1;
	private static const float MAX_DECAL_SIZE = 1.25;
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
	
	
	
	int materialColor;
	
	

	
	
	ref map<int, Decal> decalsSpawned;
	ref map<int, int> decalsFramesOfAnimation;
	ref map<int, float> decalsRotation;
	ref map<int, vector> originPosition;
	ref map<int, vector> projectionMap;
	ref map<int, float> sizeMap;

		

	const int MAX_ANIMATED_DECALS = 5;		//per character
	const int WAIT_BETWEEN_FRAMES = 50;			//in ms


	
	
	ref ScriptInvoker m_onControllableDestroyed = new ScriptInvoker();

	void OnInit(
		IEntity owner,
		World world,
		SCR_CharacterDamageManagerComponent damageManagerComponent)
	{
		m_owner = owner;
		m_world = world;
		m_damageManagerComponent = damageManagerComponent;

		decalsSpawned = new map<int, Decal>();
		decalsFramesOfAnimation = new map<int, int>();
		decalsRotation = new map<int, float>();
		originPosition = new map<int, vector>();
		projectionMap = new map<int, vector>();
		sizeMap = new map<int, float>();

		
	}
		

	void OnDamage(
			EDamageState state,
			float damage,
			inout vector hitTransform[3],)
	{
		
		materialColor = Color.FromRGBA(128, 0, 0,255).PackToInt();		//move this away
		hitPosition = hitTransform[0];
		hitDirection = hitTransform[1];
		hitDamage = damage;
				//m_OnSpeedChange.Invoke(m_fMultiplier, false);

			
		// 10 animated decals for each char... I guess?
		if (decalsSpawned.Count() < MAX_ANIMATED_DECALS)
		{

			//todo really need to make a scriptinvoker here. 
			//if (state == EDamageState.DESTROYED)
			//{
				//SpawnAnimFirstFrame(ABL_Paths.matBloodpool, true);
				//GetGame().GetCallqueue().CallLater(SpawnAnimatedFrame,WAIT_BETWEEN_FRAMES, true, ABL_Paths.matBloodpool, true);
			
			//}
			//else
			//{
			//	SpawnAnimFirstFrame(ABL_Paths.matWallDripping, false);		//should disable ground splatter then
			//	GetGame().GetCallqueue().CallLater(SpawnAnimatedFrame,WAIT_BETWEEN_FRAMES, true, ABL_Paths.matWallDripping, false);
			
			//}

			


			
		}
	}
	
	
	
		
	
	
	/*	
	
	private void SpawnAnimFirstFrame(array<ResourceName> frames, bool terrainOnly)
	{
	
		vector intersectionPosition;
		float distance = 2.0;
		
		TraceParam traceParam;
		vector origin;
		vector projection;
		
		if (terrainOnly)
		{
			traceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, Vector(0, -1, 0), distance, intersectionPosition);
			origin = m_owner.GetOrigin() + Vector(0, 2.0 / 4, 0);
		 	projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);
		
		}
		else
		{
			traceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, distance, intersectionPosition);
			origin = intersectionPosition - hitDirection * (2.0 / 4);
			
			float xProjection;
			float yProjection;
			float zProjection;
			if (hitDirection[0] < 0)
				xProjection = -0.1;
			else
				xProjection = 0.1;
			
			yProjection = 0.02;
			
			if (hitDirection[2] < 0)
				zProjection = -1;
			else
				zProjection = 1;
			
			projection = {xProjection, yProjection, zProjection};
		
		}

		if (traceParam.TraceEnt) // spawn splatter below character
		{
						
			float size = Math.RandomFloat(1.0, 2.0);
			Print(size);
			Decal tmpDecal = m_world.CreateDecal(
				traceParam.TraceEnt,
				origin, projection,
				0,
				2.0,
				Math.DEG2RAD,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				size,
				1,
				frames[0],
				-1,
				materialColor);
			
						
			
					
			SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			m_onControllableDestroyed = gameMode.GetOnControllableDestroyed();
			if (m_onControllableDestroyed)
			{
					//this should be allocated ONCE for char, not changed every singel time. redo it
					//int index = decalsSpawned.Count();
					//originPosition.Set(index,  origin);
					//projectionMap.Set(index, projection);
					//decalsSpawned.Set(index, tmpDecal);
					//sizeMap.Set(index, size);
					//decalsFramesOfAnimation.Set(index, 1);		//first frame already done
				
				
				//ABL_AnimatedDecalManager tmp = ABL_AnimatedDecalManager(0, tmpDecal, 1, Math.DEG2RAD, origin, projection, size);
				
				
				//ABL_AnimatedDecalManager animatedDecalManager = ABL_AnimatedDecalManager(
				// m_onControllableDestroyed.Insert(tmp.Run);

			}
					

				
				
				
					//todo should start after first frame. First frame here, everything else there? Or just get on weith it and pass whatever info we need right here		
		}
			

	
	}
	*/

	/*	

	private TraceParam GetSurfaceIntersection(IEntity owner,World world,vector origin,vector direction, float distance, out vector intersectionPosition)
	{
		auto param = new TraceParam();
  		param.Start = origin;
  		param.End = origin + direction * distance;
  		param.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
  		param.Exclude = owner;
		//Print("Done in GetSurfaceIntersection, going to make TraceMove");
		float intersectionDistance = world.TraceMove(param, NULL) * distance;
		//Print("Tracemove done, making stupid thing and then return");
		
		if (!intersectionDistance)
			Print("STOP!");
		
		
		intersectionPosition = origin + (direction * intersectionDistance);
		return param;
	}
	

	
	
	
	void SpawnAnimatedFrame(array<ResourceName> frames, bool terrainOnly)
	{
		foreach(int index, Decal d : decalsSpawned)
		{
			int frameIndex = decalsFramesOfAnimation.Get(index);
			if (frameIndex < ABL_Paths.matBloodpool.Count())
			{
				if (d)
					m_world.RemoveDecal(d);
					
				vector intersectionPosition;
				float distance = 2.0;
				
				TraceParam traceParam;
		
				if (terrainOnly)
					traceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, Vector(0, -1, 0), distance, intersectionPosition);
				else
					traceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, distance, intersectionPosition);
				
				
				if (traceParam.TraceEnt) // spawn splatter below character
				{	
					vector origin = originPosition.Get(index);
					vector projection = projectionMap.Get(index);
					float size = sizeMap.Get(index);
					decalsSpawned.Set(index, m_world.CreateDecal(traceParam.TraceEnt, origin, projection, 
							0, 2.0, Math.DEG2RAD, size, 1, frames[frameIndex], -1, materialColor));
					frameIndex++;
					decalsFramesOfAnimation.Set(index, frameIndex);
				}	
			}
			else
			{
				decalsFramesOfAnimation.Remove(index);
				decalsSpawned.Remove(index);
				GetGame().GetCallqueue().Remove(SpawnAnimatedFrame);
			}
			
		}
	}
	
	
	
	
	
	// OLD!!!!!!!!!!!!!!!!!!!
	
	/* FIRST FRAMES 
		void SpawnAnimatedBloodDrippingFirstFrame()
	{
		vector intersectionPosition;
		auto surfaceTraceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, 2, intersectionPosition);


		if (surfaceTraceParam.TraceEnt) // spawn splatter on surface
		{
			
			Print("Starting spawn first frame");
			//todo I really need to udnerstand how these values work.
			//vector origin = m_owner.GetOrigin() - hitPosition;// * (BL_Constants.DECAL_FAR_PLANE / 4);
			//vector projection = hitDirection;		//using the direction... so it shoulnd't be changed, projection is totally correct. The problem is the origin...? No 
			
			//float rotation = Math.RandomFloat(0, 45) * Math.DEG2RAD;
			
			// color must be set HERE
			
			materialColor = Color.FromRGBA(128, 0, 0,255).PackToInt();		//move this away
			
			
			vector origin = intersectionPosition - hitDirection * (2.0 / 4);
			
			
			
			//if (origin[1] < 2.0)
			//	origin[1] = origin[1] + 1.0;
			float xProjection;
			float yProjection;
			float zProjection;
			
			
			if (hitDirection[0] < 0)
				xProjection = -0.1;
			else
				xProjection = 0.1;
			
			yProjection = 0.02;
			
			if (hitDirection[2] < 0)
				zProjection = -1;
			else
				zProjection = 1;
			
			
			
			vector projection = {xProjection, yProjection, zProjection};
			Print(origin);
			Print(projection);
			Print("_________________________");

			Decal tmpDecal  = m_world.CreateDecal(
				surfaceTraceParam.TraceEnt,
				origin,
				projection,
				0,
				2.0,
				Math.DEG2RAD,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				1.0, //Math.RandomFloat(MIN_DECAL_SIZE, MAX_DECAL_SIZE),
				1,
				ABL_Paths.matWallDripping[0],
				-1,
				materialColor
			);
			
			
			
			
			//Decal tmpDecal = m_world.CreateDecal(surfaceTraceParam.TraceEnt, origin, projection, 0, 2.0,
			//	180, 1.0, 1, materials[0], -1,  materialColor);
			
			//Print("First frame spawned");
			
			int index = decalsSpawned.Count();
			originPosition.Set(index,  origin);
			projectionMap.Set(index, projection);
			decalsSpawned.Set(index, tmpDecal);
			decalsFramesOfAnimation.Set(index, 1);		//first frame already done
		}
		
	}
	
	
	void SpawnAnimatedBloodpoolFirstFrame()
	{
		vector intersectionPosition;


		// attempt ground splatter
		auto groundTraceParam = GetSurfaceIntersection(
			m_owner,
			m_world,
			hitPosition,
			Vector(0, -1, 0),
			2.0,
			intersectionPosition
		);
		if (groundTraceParam.TraceEnt) // spawn splatter below character
		{
			
			vector origin = m_owner.GetOrigin() + Vector(0, 2.0 / 4, 0);
			vector projection = vector.Lerp(-groundTraceParam.TraceNorm, hitDirection, 0.5);
			
			Decal tmpDecal = m_world.CreateDecal(
				groundTraceParam.TraceEnt,
				origin, projection,
				0,
				2.0,
				Math.DEG2RAD,   //Math.RandomFloat(0, 360) * Math.DEG2RAD,
				1.0, //Math.RandomFloat(MIN_DECAL_SIZE, MAX_DECAL_SIZE),
				1,
				ABL_Paths.matBloodpool[0],
				-1,
				materialColor
			);
			
						
			int index = decalsSpawned.Count();
			originPosition.Set(index,  origin);
			projectionMap.Set(index, projection);
			decalsSpawned.Set(index, tmpDecal);
			decalsFramesOfAnimation.Set(index, 1);		//first frame already done
		}
	
	
	}

	
	/* Continue animations 
	
	
	void SpawnAnimatedBloodpool()
	{
		foreach(int index, Decal d : decalsSpawned)
		{
			int frameIndex = decalsFramesOfAnimation.Get(index);
			if (frameIndex < ABL_Paths.matBloodpool.Count())
			{
				if (d)
					m_world.RemoveDecal(d);
					
	
				vector intersectionPosition;
			
				auto surfaceTraceParam = GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, 2, intersectionPosition);
				if (surfaceTraceParam.TraceEnt) // spawn splatter below character
				{	
					vector origin = originPosition.Get(index);
					vector projection = projectionMap.Get(index);
					decalsSpawned.Set(index, m_world.CreateDecal(surfaceTraceParam.TraceEnt, origin, projection, 
							0, 2.0, Math.DEG2RAD, 1.0, 1, ABL_Paths.matBloodpool[frameIndex], -1, materialColor));
					frameIndex++;
					decalsFramesOfAnimation.Set(index, frameIndex);
				}	
			}
			else
			{
				decalsFramesOfAnimation.Remove(index);
				decalsSpawned.Remove(index);
				GetGame().GetCallqueue().Remove(SpawnAnimatedBloodpool);
			}
			
		}
	
	}

	void SpawnAnimatedBloodDripping()
	{
		//todo this needs to be in a dedicated class separated from the character to prevent stopping from death 

		foreach(int index, Decal d : decalsSpawned)
		{
			//Print("Decal: " + index);
			int frameIndex = decalsFramesOfAnimation.Get(index);
			//Print("Frame: " + frameIndex);
			


			
			if (frameIndex < ABL_Paths.matWallDripping.Count())
			{
				//updates animation frames for already spawned decals 
				if (d)
					m_world.RemoveDecal(d);
				

				vector intersectionPosition;
		
				// attempt surface splatter, using the hitDirection as a "trigger"
				auto groundTraceParam = GetSurfaceIntersection(m_owner,m_world,hitPosition,Vector(0, -1, 0),2.0,intersectionPosition);	
				if (groundTraceParam.TraceEnt) // spawn splatter below character
				{
					vector origin = originPosition.Get(index);
					vector projection = projectionMap.Get(index);
					

					decalsSpawned.Set(index, m_world.CreateDecal(groundTraceParam.TraceEnt, origin, projection, 0, 2.0, Math.DEG2RAD,  1.0, 1, ABL_Paths.matWallDripping[frameIndex], -1, materialColor));
					frameIndex++;
					decalsFramesOfAnimation.Set(index, frameIndex);
				}	
			}
			else
			{
				// FINISHED ANIMATION
				decalsFramesOfAnimation.Remove(index);
				decalsSpawned.Remove(index);
				GetGame().GetCallqueue().Remove(SpawnAnimatedBloodDripping);
			}
			
			
			
			

			
		}
		

	
		// attempt surface splatter, using the hitDirection as a "trigger"
		auto surfaceTraceParam = BL_Utilities.GetSurfaceIntersection(m_owner, m_world, hitPosition, hitDirection, BL_Constants.SURFACE_SPLATTER_INTERSECTION_DISTANCE, intersectionPosition);
		if (surfaceTraceParam.TraceEnt) // spawn splatter below character
		{
			 m_world.CreateDecal(surfaceTraceParam.TraceEnt, intersectionPosition - hitDirection * (BL_Constants.DECAL_FAR_PLANE / 4), hitDirection, 0, BL_Constants.DECAL_FAR_PLANE, 0,  
				1.0, 1, materials[currentIndex], BL_Constants.DECAL_LIFETIME_SECS, materialColor);
		}	
	

	}
	

*/
	
	

}