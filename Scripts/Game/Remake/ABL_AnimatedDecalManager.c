class ABL_AnimatedDecalManagerClass : GenericEntityClass
{}




class ABL_AnimatedDecalManager : GenericEntity
{
	
	ref map<EDecalType, ref array<ResourceName>> animationMaterials;
	ref map<int, ref DecalInformation> decalsSpawned;

	// 1) must be initialized one time 
	// 2) each char will relate to this.
	//3) should be spawned at runtime, maybe first char that spawns actualy spawn this. So for now let's just usemake it really stupid and get the entity from the world
	

	static ABL_AnimatedDecalManager instance;
	
	
	private World m_world;
	int materialColor;	//todo make this dynamic 
	const float WAIT_TIME = 0.1;		//100 ms
	float currentTime;

	
	
	
	
	
	static ABL_AnimatedDecalManager GetInstance()
	{
		return instance;
	}

	
	
	void ABL_AnimatedDecalManager(IEntitySource src, IEntity parent)
	{

		SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
		SetFlags(EntityFlags.ACTIVE, true);
		
		
		
		Print("ADM: Starting up ADM");
		decalsSpawned = new map<int, ref DecalInformation>();
		animationMaterials = new map<EDecalType, ref array<ResourceName>>();
		animationMaterials.Insert(EDecalType.BLOODPOOL, {"{B1934F7967DAD951}materials/bloodpool/1.emat","{502E981AD9811291}materials/bloodpool/2.emat","{A426DF82D45C7AE5}materials/bloodpool/3.emat",
			"{EDFECA9DA69A0E8F}materials/bloodpool/4.emat","{19F68D05AB4766FB}materials/bloodpool/5.emat","{471EA44614CAE8F4}materials/bloodpool/6.emat","{B316E3DE19178080}materials/bloodpool/7.emat",
			"{D4AE8E78F1460020}materials/bloodpool/8.emat","{20A6C9E0FC9B6854}materials/bloodpool/9.emat","{5DFCEE9E8D12D299}materials/bloodpool/10.emat","{A9F4A90680CFBAED}materials/bloodpool/11.emat",
			"{F71C80453F4234E2}materials/bloodpool/12.emat","{0314C7DD329F5C96}materials/bloodpool/13.emat","{4ACCD2C2405928FC}materials/bloodpool/14.emat","{BEC4955A4D844088}materials/bloodpool/15.emat",
			"{E02CBC19F209CE87}materials/bloodpool/16.emat","{1424FB81FFD4A6F3}materials/bloodpool/17.emat","{739C962717852653}materials/bloodpool/18.emat","{8794D1BF1A584E27}materials/bloodpool/19.emat",
			"{5759BED33B02211E}materials/bloodpool/20.emat","{A351F94B36DF496A}materials/bloodpool/21.emat","{FDB9D0088952C765}materials/bloodpool/22.emat","{09B19790848FAF11}materials/bloodpool/23.emat",
			"{4069828FF649DB7B}materials/bloodpool/24.emat","{B461C517FB94B30F}materials/bloodpool/25.emat","{EA89EC5444193D00}materials/bloodpool/26.emat","{1E81ABCC49C45574}materials/bloodpool/27.emat",
			"{7939C66AA195D5D4}materials/bloodpool/28.emat","{8D3181F2AC48BDA0}materials/bloodpool/29.emat","{90952E4ECE546212}materials/bloodpool/30.emat","{649D69D6C3890A66}materials/bloodpool/31.emat",
			"{3A7540957C048469}materials/bloodpool/32.emat","{CE7D070D71D9EC1D}materials/bloodpool/33.emat","{87A51212031F9877}materials/bloodpool/34.emat","{73AD558A0EC2F003}materials/bloodpool/35.emat",
			"{2D457CC9B14F7E0C}materials/bloodpool/36.emat","{D94D3B51BC921678}materials/bloodpool/37.emat","{BEF556F754C396D8}materials/bloodpool/38.emat","{4AFD116F591EFEAC}materials/bloodpool/39.emat",
			"{42131E485723C610}materials/bloodpool/40.emat","{B61B59D05AFEAE64}materials/bloodpool/41.emat","{E8F37093E573206B}materials/bloodpool/42.emat","{1CFB370BE8AE481F}materials/bloodpool/43.emat",
			"{552322149A683C75}materials/bloodpool/44.emat","{A12B658C97B55401}materials/bloodpool/45.emat","{FFC34CCF2838DA0E}materials/bloodpool/46.emat","{0BCB0B5725E5B27A}materials/bloodpool/47.emat",
			"{6C7366F1CDB432DA}materials/bloodpool/48.emat","{987B2169C0695AAE}materials/bloodpool/49.emat"});
		

		animationMaterials.Insert(EDecalType.GENERIC_SPLATTER, {"{9BF28FFBA19F287D}materials/wall_splatter/0.emat","{1FFD03D5B7529B65}materials/wall_splatter/1.emat","{3112E12013CFCE06}materials/wall_splatter/2.emat",
			"{C51AA6B81E12A672}materials/wall_splatter/3.emat","{8CC2B3A76CD4D218}materials/wall_splatter/4.emat","{78CAF43F6109BA6C}materials/wall_splatter/5.emat","{2622DD7CDE843463}materials/wall_splatter/6.emat","{D22A9AE4D3595C17}materials/wall_splatter/7.emat",
			"{B592F7423B08DCB7}materials/wall_splatter/8.emat","{419AB0DA36D5B4C3}materials/wall_splatter/9.emat","{350AC655A18B59FB}materials/wall_splatter/10.emat","{C10281CDAC56318F}materials/wall_splatter/11.emat","{9FEAA88E13DBBF80}materials/wall_splatter/12.emat",
			"{6BE2EF161E06D7F4}materials/wall_splatter/13.emat","{223AFA096CC0A39E}materials/wall_splatter/14.emat","{D632BD91611DCBEA}materials/wall_splatter/15.emat","{88DA94D2DE9045E5}materials/wall_splatter/16.emat","{7CD2D34AD34D2D91}materials/wall_splatter/17.emat",
			"{1B6ABEEC3B1CAD31}materials/wall_splatter/18.emat","{EF62F97436C1C545}materials/wall_splatter/19.emat","{3FAF9618179BAA7C}materials/wall_splatter/20.emat","{CBA7D1801A46C208}materials/wall_splatter/21.emat","{954FF8C3A5CB4C07}materials/wall_splatter/22.emat",
			"{6147BF5BA8162473}materials/wall_splatter/23.emat","{289FAA44DAD05019}materials/wall_splatter/24.emat","{DC97EDDCD70D386D}materials/wall_splatter/25.emat","{827FC49F6880B662}materials/wall_splatter/26.emat","{76778307655DDE16}materials/wall_splatter/27.emat",
			"{11CFEEA18D0C5EB6}materials/wall_splatter/28.emat","{E5C7A93980D136C2}materials/wall_splatter/29.emat","{F8630685E2CDE970}materials/wall_splatter/30.emat","{0C6B411DEF108104}materials/wall_splatter/31.emat","{5283685E509D0F0B}materials/wall_splatter/32.emat",
			"{A68B2FC65D40677F}materials/wall_splatter/33.emat","{EF533AD92F861315}materials/wall_splatter/34.emat","{1B5B7D41225B7B61}materials/wall_splatter/35.emat","{45B354029DD6F56E}materials/wall_splatter/36.emat","{B1BB139A900B9D1A}materials/wall_splatter/37.emat",
			"{D6037E3C785A1DBA}materials/wall_splatter/38.emat","{220B39A4758775CE}materials/wall_splatter/39.emat","{2AE536837BBA4D72}materials/wall_splatter/40.emat","{DEED711B76672506}materials/wall_splatter/41.emat","{80055858C9EAAB09}materials/wall_splatter/42.emat",
			"{740D1FC0C437C37D}materials/wall_splatter/43.emat","{3DD50ADFB6F1B717}materials/wall_splatter/44.emat","{C9DD4D47BB2CDF63}materials/wall_splatter/45.emat","{9735640404A1516C}materials/wall_splatter/46.emat","{633D239C097C3918}materials/wall_splatter/47.emat",
			"{04854E3AE12DB9B8}materials/wall_splatter/48.emat","{F08D09A2ECF0D1CC}materials/wall_splatter/49.emat","{ED29A61E8EEC0E7E}materials/wall_splatter/50.emat","{1921E1868331660A}materials/wall_splatter/51.emat","{47C9C8C53CBCE805}materials/wall_splatter/52.emat",
			"{B3C18F5D31618071}materials/wall_splatter/53.emat","{FA199A4243A7F41B}materials/wall_splatter/54.emat","{0E11DDDA4E7A9C6F}materials/wall_splatter/55.emat","{50F9F499F1F71260}materials/wall_splatter/56.emat","{A4F1B301FC2A7A14}materials/wall_splatter/57.emat",
			"{C349DEA7147BFAB4}materials/wall_splatter/58.emat","{3741993F19A692C0}materials/wall_splatter/59.emat","{E78CF65338FCFDF9}materials/wall_splatter/60.emat","{1384B1CB3521958D}materials/wall_splatter/61.emat","{4D6C98888AAC1B82}materials/wall_splatter/62.emat",
			"{B964DF10877173F6}materials/wall_splatter/63.emat"});
		
		
		instance = this;
		
		
	}

	override void EOnInit(IEntity owner) //!EntityEvent.INIT
	{
		super.EOnInit(owner);
		//Allocate it whenever called. When called, let's start. 

		
		
		
		
		

		m_world = GetGame().GetWorld();
		materialColor = Color.FromRGBA(128, 0, 0,255).PackToInt();		//move this away
	}
    
	
	override void EOnFrame(IEntity owner, float timeSlice) //!EntityEvent.FRAME
	{
		//Print("ADM: Running");
		
		GetGame().GetCallqueue().Tick(timeSlice);		//Maybe?
		
		
		if (decalsSpawned.Count() > 0)
		{
			currentTime += timeSlice;
			
			if (currentTime > WAIT_TIME)
			{
				SpawnAnimatedFrames();
				currentTime = 0;

			}

		
		}
		else
			return;
		
		
		
		
		
		//Print("Do something come on");
		//if (decalsSpawned.Count() > 0 && currentTime)
	//	{
	//		SpawnAnimatedFrames();
	//	}
	//	else 
	//		return;
	}
	
	
	
	//void SetupNewAnimation(int index, Decal dec, int frames, float rot, vector orig, vector proj, int si)
	void StartNewAnimation(IEntity character, vector hitPosition, vector hitDirection, EDecalType type, bool terrainOnly)
	{
		
		
		//TEMP FIX! 
		
		
		
		
		
		
		//Print("Shot " + character);
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
			DecalInformation tmpDecalInformation = new DecalInformation(tmpDecal, type, 1, traceParam, hitPosition, hitDirection, origin, projection, size, Math.DEG2RAD, terrainOnly); 
			decalsSpawned.Insert(index, tmpDecalInformation);
			
			//GetGame().GetCallqueue().CallLater(SpawnAnimatedFrames, WAIT_TIME, true);
	
		}

	}
	
	
	void SpawnAnimatedFrames()
	{
		
		float distance = 2.0;

		foreach(int index, DecalInformation dInfo : decalsSpawned)
		{
			
			Decal d = dInfo.decal;
			int currentFrame = dInfo.currentFrame;
			array<ResourceName> tempFrames = animationMaterials.Get(dInfo.type);
			
			if (currentFrame < tempFrames.Count())
			{
				if (d)
					m_world.RemoveDecal(d);
					
				TraceParam traceParam = dInfo.traceParam;
				
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
				GetGame().GetCallqueue().Remove(SpawnAnimatedFrames);
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
	//IEntity character;
	Decal decal; 
	EDecalType type;
	int currentFrame;
	
	ref TraceParam traceParam;
	vector hitPosition;
	vector hitDirection;
	vector originPosition;
	vector projectionDirection;
	
	float size;
	float rotation;
	
	bool terrainOnly;
	
	void DecalInformation( Decal d, EDecalType t, int cf, TraceParam tp, vector hp, vector hd, vector op, vector pd, float s, float r, bool to)
	{
		//character = c;
		decal = d;
		type = t;
		currentFrame = cf;
		traceParam = tp;
		hitPosition = hp;
		hitDirection = hd;
		originPosition = op;
		projectionDirection = pd;
		size = s;
		rotation = r;
		terrainOnly = to;
	}
}

enum EDecalType
{
	BLOODPOOL,
	GENERIC_SPLATTER
}
