class ABL_AnimatedDecalManagerClass : GenericEntityClass
{}




class ABL_AnimatedDecalManager : GenericEntity
{
	
	ref map<EDecalType, array<ResourceName>> animationMaterials;
	ref map<int, DecalInformation> decalsSpawned;

	// 1) must be initialized one time 
	// 2) each char will relate to this.
	//3) should be spawned at runtime, maybe first char that spawns actualy spawn this. So for now let's just usemake it really stupid and get the entity from the world
	

	ABL_AnimatedDecalManager instance;
	
	
	private World m_world;
	int materialColor;	//todo make this dynamic 


	void ABL_AnimatedDecalManager(IEntitySource src, IEntity parent)
	{

		SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
		SetFlags(EntityFlags.ACTIVE, true);
		
	}

	override void EOnInit(IEntity owner) //!EntityEvent.INIT
	{
		super.EOnInit(owner);
		//Allocate it whenever called. When called, let's start. 
		Print("ADM: Starting up ADM");
		decalsSpawned = new map<int, DecalInformation>();
		
		animationMaterials = new map<EDecalType, array<ResourceName>>();
		animationMaterials.Insert(EDecalType.BLOODPOOL, {"{B1934F7967DAD951}bloodpool/materials/1.emat", "{459B08E16A07B125}bloodpool/materials/0.emat","{B1934F7967DAD951}bloodpool/materials/1.emat","{EF7B663AD857575E}bloodpool/materials/2.emat",
		"{1B7321A2D58A3F2A}bloodpool/materials/3.emat","{52AB34BDA74C4B40}bloodpool/materials/4.emat","{A6A37325AA912334}bloodpool/materials/5.emat","{F84B5A66151CAD3B}bloodpool/materials/6.emat",
		"{0C431DFE18C1C54F}bloodpool/materials/7.emat","{6BFB7058F09045EF}bloodpool/materials/8.emat","{9FF337C0FD4D2D9B}bloodpool/materials/9.emat","{48FB2AAC7FBE89B1}bloodpool/materials/10.emat",
		"{BCF36D347263E1C5}bloodpool/materials/11.emat","{E21B4477CDEE6FCA}bloodpool/materials/12.emat","{161303EFC03307BE}bloodpool/materials/13.emat","{5FCB16F0B2F573D4}bloodpool/materials/14.emat",
		"{ABC35168BF281BA0}bloodpool/materials/15.emat","{F52B782B00A595AF}bloodpool/materials/16.emat","{01233FB30D78FDDB}bloodpool/materials/17.emat","{669B5215E5297D7B}bloodpool/materials/18.emat",
		"{9293158DE8F4150F}bloodpool/materials/19.emat","{425E7AE1C9AE7A36}bloodpool/materials/20.emat","{B6563D79C4731242}bloodpool/materials/21.emat","{E8BE143A7BFE9C4D}bloodpool/materials/22.emat",
		"{1CB653A27623F439}bloodpool/materials/23.emat","{556E46BD04E58053}bloodpool/materials/24.emat","{A16601250938E827}bloodpool/materials/25.emat","{FF8E2866B6B56628}bloodpool/materials/26.emat",
		"{0B866FFEBB680E5C}bloodpool/materials/27.emat","{6C3E025853398EFC}bloodpool/materials/28.emat","{983645C05EE4E688}bloodpool/materials/29.emat","{8592EA7C3CF8393A}bloodpool/materials/30.emat",
		"{719AADE43125514E}bloodpool/materials/31.emat","{2F7284A78EA8DF41}bloodpool/materials/32.emat","{DB7AC33F8375B735}bloodpool/materials/33.emat","{92A2D620F1B3C35F}bloodpool/materials/34.emat",
		"{66AA91B8FC6EAB2B}bloodpool/materials/35.emat","{3842B8FB43E32524}bloodpool/materials/36.emat","{CC4AFF634E3E4D50}bloodpool/materials/37.emat","{ABF292C5A66FCDF0}bloodpool/materials/38.emat",
		"{5FFAD55DABB2A584}bloodpool/materials/39.emat","{5714DA7AA58F9D38}bloodpool/materials/40.emat","{A31C9DE2A852F54C}bloodpool/materials/41.emat","{FDF4B4A117DF7B43}bloodpool/materials/42.emat",
		"{09FCF3391A021337}bloodpool/materials/43.emat","{4024E62668C4675D}bloodpool/materials/44.emat","{B42CA1BE65190F29}bloodpool/materials/45.emat","{EAC488FDDA948126}bloodpool/materials/46.emat",
		"{1ECCCF65D749E952}bloodpool/materials/47.emat","{7974A2C33F1869F2}bloodpool/materials/48.emat","{8D7CE55B32C50186}bloodpool/materials/49.emat"});
		
		
		animationMaterials.Insert(EDecalType.GENERIC_SPLATTER, {"{C7ADE32E13BAE5F3}test3/materials/0.emat","{1FFD03D5B7529B65}test3/materials/1.emat","{41152A9608DF156A}test3/materials/2.emat",
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
		"{40C8A431523351DE}test3/materials/59.emat","{9005CB5D73693EE7}test3/materials/60.emat","{640D8CC57EB45693}test3/materials/61.emat","{3AE5A586C139D89C}test3/materials/62.emat",
		"{CEEDE21ECCE4B0E8}test3/materials/63.emat"});
		
		
		
		
		
		
		

		m_world = GetGame().GetWorld();
		materialColor = Color.FromRGBA(128, 0, 0,255).PackToInt();		//move this away
	}
    
	
	override void EOnFrame(IEntity owner, float timeSlice) //!EntityEvent.FRAME
	{
		//Print("ADM: Running");
		if (decalsSpawned.Count() > 0)
		{
			Print("Decals to animate");
		}
		else 
			return;
	}
	
	
	
	//void SetupNewAnimation(int index, Decal dec, int frames, float rot, vector orig, vector proj, int si)
	void StartNewAnimation(IEntity character, vector hitPosition, vector hitDirection, EDecalType type, bool terrainOnly)
	{
		
		vector intersectionPosition;
		float distance = 2.0;
		TraceParam traceParam;
		vector origin;
		vector projection;
		array<ResourceName> tempFrames = animationMaterials.Get(type);

		if (terrainOnly)
		{
			traceParam = GetSurfaceIntersection(character, m_world, hitPosition, Vector(0, -1, 0), distance, intersectionPosition);
			origin = character.GetOrigin() + Vector(0, 2.0 / 4, 0);
		 	projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);
		
		}
		else
		{
			traceParam = GetSurfaceIntersection(character, m_world, hitPosition, hitDirection, distance, intersectionPosition);
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
				tempFrames[0],
				-1,
				materialColor);
			
						
			int index = decalsSpawned.Count();
			DecalInformation tmpDecalInformation = DecalInformation(character, tmpDecal, type, 1,  hitPosition, hitDirection, origin, projection, size, Math.DEG2RAD); 
			decalsSpawned.Insert(index, tmpDecalInformation);
	
		}

	}
	
	
	void SpawnAnimatedFrame(IEntity character, bool terrainOnly)
	{
		
		float distance = 2.0;

		foreach(int index, DecalInformation dInfo : decalsSpawned)
		{
			
			Decal d = dInfo.decal;
			int currentFrame = dInfo.currentFrame;
		
			
			
			
			//int frameIndex = decalsFramesOfAnimation.Get(index);
			array<ResourceName> tempFrames = animationMaterials.Get(dInfo.type);
			
			if (currentFrame < tempFrames.Count())
			{
				if (d)
					m_world.RemoveDecal(d);
					
				vector intersectionPosition;
				TraceParam traceParam;
		
				if (terrainOnly)
					traceParam = GetSurfaceIntersection(dInfo.character, m_world, dInfo.hitPosition, Vector(0, -1, 0), distance, intersectionPosition);
				else
					traceParam = GetSurfaceIntersection(dInfo.character, m_world, dInfo.hitPosition, dInfo.hitDirection, distance, intersectionPosition);
				
				
				if (traceParam.TraceEnt) // spawn splatter below character
				{	

					Decal newDecal = m_world.CreateDecal(traceParam.TraceEnt, dInfo.originPosition, dInfo.projectionDirection, 
							0, 2.0, dInfo.rotation, dInfo.size, 1, tempFrames[currentFrame], -1, materialColor);
					
					currentFrame++;
					
					dInfo.decal = newDecal;
					dInfo.currentFrame = currentFrame;
					decalsSpawned.Set(index, dInfo);		//reset it... not sure if it's needed tbh
				}	
			}
			else
			{
				decalsSpawned.Remove(index);
				GetGame().GetCallqueue().Remove(SpawnAnimatedFrame);
			}
			
		}
	}
	
	// Helpers 
	private TraceParam GetSurfaceIntersection(IEntity owner,World world,vector origin,vector direction, float distance, out vector intersectionPosition)
	{
		auto param = new TraceParam();
  		param.Start = origin;
  		param.End = origin + direction * distance;
  		param.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
  		param.Exclude = owner;
		float intersectionDistance = world.TraceMove(param, NULL) * distance;
		
		if (!intersectionDistance)
			Print("STOP!");
		
		
		intersectionPosition = origin + (direction * intersectionDistance);
		return param;
	}
	
	
	
}



class DecalInformation
{
	IEntity character;
	Decal decal; 
	EDecalType type;
	int currentFrame;
	vector hitPosition;
	vector hitDirection;
	vector originPosition;
	vector projectionDirection;
	
	float size;
	float rotation;
	
	
	void DecalInformation(IEntity c, Decal d, EDecalType t, int cf, vector hp, vector hd, vector op, vector pd, float s, float r)
	{
		character = c;
		decal = d;
		type = t;
		currentFrame = cf;
		hitPosition = hp;
		hitDirection = hd;
		originPosition = op;
		projectionDirection = pd;
		size = s;
		rotation = r;
	}
}

enum EDecalType
{
	BLOODPOOL,
	GENERIC_SPLATTER
}
