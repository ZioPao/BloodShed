class ABL_AnimatedDecalManagerClass : GenericEntityClass
{}



//todo implement weapon cleaning 



class ABL_AnimatedDecalManager : GenericEntity
{
	
	ref map<EDecalType, ref array<ResourceName>> animationMaterials;
	ref map<int, ref DecalInformation> decalsSpawned;
	const string ABL_MOD_ID = "59951797A291CA02";				//it's probably possible to get this in a better way but ok

	// 1) must be initialized one time 
	// 2) each char will relate to this.
	//3) should be spawned at runtime, maybe first char that spawns actualy spawn this. So for now let's just usemake it really stupid and get the entity from the world
	

	static ABL_AnimatedDecalManager instance;
	
	
	private World m_world;
	int materialColor;	//todo make this dynamic 
	float waitTimeBetweenFrames;
	float currentTime;

	//ref map<string, string> ablSettings;

	
	
	
	
	const float nearClip = 0.0;
	const float farClip = 5;
	
	
	
	ref map<string, string> settings;
	
	
	
	
	ref map<string, string> waitBetweenFrames
	
	
	
	static ABL_AnimatedDecalManager GetInstance()
	{
		return instance;
	}

	
	
	void ABL_AnimatedDecalManager(IEntitySource src, IEntity parent)
	{

		SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
		SetFlags(EntityFlags.ACTIVE, true);
		
		 Math.Randomize(-1);
		
		//Print("ADM: Starting up ADM");
		decalsSpawned = new map<int, ref DecalInformation>();
		animationMaterials = new map<EDecalType, ref array<ResourceName>>();
		
		//animationMaterials.Insert(EDecalType.BLOODPOOL, {"{0EC6B159660C9C9E}materials/bloodpool/1.emat","{502E981AD9811291}materials/bloodpool/2.emat","{A426DF82D45C7AE5}materials/bloodpool/3.emat","{EDFECA9DA69A0E8F}materials/bloodpool/4.emat","{19F68D05AB4766FB}materials/bloodpool/5.emat","{471EA44614CAE8F4}materials/bloodpool/6.emat","{B316E3DE19178080}materials/bloodpool/7.emat","{D4AE8E78F1460020}materials/bloodpool/8.emat","{20A6C9E0FC9B6854}materials/bloodpool/9.emat","{5DFCEE9E8D12D299}materials/bloodpool/10.emat","{A9F4A90680CFBAED}materials/bloodpool/11.emat","{F71C80453F4234E2}materials/bloodpool/12.emat","{0314C7DD329F5C96}materials/bloodpool/13.emat","{4ACCD2C2405928FC}materials/bloodpool/14.emat","{BEC4955A4D844088}materials/bloodpool/15.emat","{E02CBC19F209CE87}materials/bloodpool/16.emat","{1424FB81FFD4A6F3}materials/bloodpool/17.emat","{739C962717852653}materials/bloodpool/18.emat","{8794D1BF1A584E27}materials/bloodpool/19.emat","{5759BED33B02211E}materials/bloodpool/20.emat","{A351F94B36DF496A}materials/bloodpool/21.emat","{FDB9D0088952C765}materials/bloodpool/22.emat","{09B19790848FAF11}materials/bloodpool/23.emat","{4069828FF649DB7B}materials/bloodpool/24.emat","{B461C517FB94B30F}materials/bloodpool/25.emat","{EA89EC5444193D00}materials/bloodpool/26.emat","{1E81ABCC49C45574}materials/bloodpool/27.emat","{7939C66AA195D5D4}materials/bloodpool/28.emat","{8D3181F2AC48BDA0}materials/bloodpool/29.emat","{90952E4ECE546212}materials/bloodpool/30.emat","{649D69D6C3890A66}materials/bloodpool/31.emat","{3A7540957C048469}materials/bloodpool/32.emat","{CE7D070D71D9EC1D}materials/bloodpool/33.emat","{87A51212031F9877}materials/bloodpool/34.emat","{73AD558A0EC2F003}materials/bloodpool/35.emat","{2D457CC9B14F7E0C}materials/bloodpool/36.emat","{D94D3B51BC921678}materials/bloodpool/37.emat","{BEF556F754C396D8}materials/bloodpool/38.emat","{4AFD116F591EFEAC}materials/bloodpool/39.emat","{42131E485723C610}materials/bloodpool/40.emat","{B61B59D05AFEAE64}materials/bloodpool/41.emat","{E8F37093E573206B}materials/bloodpool/42.emat","{1CFB370BE8AE481F}materials/bloodpool/43.emat","{552322149A683C75}materials/bloodpool/44.emat","{A12B658C97B55401}materials/bloodpool/45.emat","{FFC34CCF2838DA0E}materials/bloodpool/46.emat","{0BCB0B5725E5B27A}materials/bloodpool/47.emat","{6C7366F1CDB432DA}materials/bloodpool/48.emat","{987B2169C0695AAE}materials/bloodpool/49.emat"}); 
		animationMaterials.Insert(EDecalType.BLOODPOOL, {"{0B3E3364946978F1}materials/bloodpool/HFMaterials/001.emat","{55D61A272BE4F6FE}materials/bloodpool/HFMaterials/002.emat","{A1DE5DBF26399E8A}materials/bloodpool/HFMaterials/003.emat","{E80648A054FFEAE0}materials/bloodpool/HFMaterials/004.emat","{1C0E0F3859228294}materials/bloodpool/HFMaterials/005.emat","{42E6267BE6AF0C9B}materials/bloodpool/HFMaterials/006.emat","{B6EE61E3EB7264EF}materials/bloodpool/HFMaterials/007.emat","{D1560C450323E44F}materials/bloodpool/HFMaterials/008.emat","{255E4BDD0EFE8C3B}materials/bloodpool/HFMaterials/009.emat","{38FAE4616CE25389}materials/bloodpool/HFMaterials/010.emat","{CCF2A3F9613F3BFD}materials/bloodpool/HFMaterials/011.emat","{921A8ABADEB2B5F2}materials/bloodpool/HFMaterials/012.emat","{6612CD22D36FDD86}materials/bloodpool/HFMaterials/013.emat","{2FCAD83DA1A9A9EC}materials/bloodpool/HFMaterials/014.emat","{DBC29FA5AC74C198}materials/bloodpool/HFMaterials/015.emat","{852AB6E613F94F97}materials/bloodpool/HFMaterials/016.emat","{7122F17E1E2427E3}materials/bloodpool/HFMaterials/017.emat","{169A9CD8F675A743}materials/bloodpool/HFMaterials/018.emat","{E292DB40FBA8CF37}materials/bloodpool/HFMaterials/019.emat","{325FB42CDAF2A00E}materials/bloodpool/HFMaterials/020.emat","{C657F3B4D72FC87A}materials/bloodpool/HFMaterials/021.emat","{98BFDAF768A24675}materials/bloodpool/HFMaterials/022.emat","{6CB79D6F657F2E01}materials/bloodpool/HFMaterials/023.emat","{256F887017B95A6B}materials/bloodpool/HFMaterials/024.emat","{D167CFE81A64321F}materials/bloodpool/HFMaterials/025.emat","{8F8FE6ABA5E9BC10}materials/bloodpool/HFMaterials/026.emat","{7B87A133A834D464}materials/bloodpool/HFMaterials/027.emat","{1C3FCC95406554C4}materials/bloodpool/HFMaterials/028.emat","{E8378B0D4DB83CB0}materials/bloodpool/HFMaterials/029.emat","{F59324B12FA4E302}materials/bloodpool/HFMaterials/030.emat","{019B632922798B76}materials/bloodpool/HFMaterials/031.emat","{5F734A6A9DF40579}materials/bloodpool/HFMaterials/032.emat","{AB7B0DF290296D0D}materials/bloodpool/HFMaterials/033.emat","{E2A318EDE2EF1967}materials/bloodpool/HFMaterials/034.emat","{16AB5F75EF327113}materials/bloodpool/HFMaterials/035.emat","{4843763650BFFF1C}materials/bloodpool/HFMaterials/036.emat","{BC4B31AE5D629768}materials/bloodpool/HFMaterials/037.emat","{DBF35C08B53317C8}materials/bloodpool/HFMaterials/038.emat","{2FFB1B90B8EE7FBC}materials/bloodpool/HFMaterials/039.emat","{271514B7B6D34700}materials/bloodpool/HFMaterials/040.emat","{D31D532FBB0E2F74}materials/bloodpool/HFMaterials/041.emat","{8DF57A6C0483A17B}materials/bloodpool/HFMaterials/042.emat","{79FD3DF4095EC90F}materials/bloodpool/HFMaterials/043.emat","{302528EB7B98BD65}materials/bloodpool/HFMaterials/044.emat","{C42D6F737645D511}materials/bloodpool/HFMaterials/045.emat","{9AC54630C9C85B1E}materials/bloodpool/HFMaterials/046.emat","{6ECD01A8C415336A}materials/bloodpool/HFMaterials/047.emat","{09756C0E2C44B3CA}materials/bloodpool/HFMaterials/048.emat","{FD7D2B962199DBBE}materials/bloodpool/HFMaterials/049.emat","{E0D9842A4385040C}materials/bloodpool/HFMaterials/050.emat","{14D1C3B24E586C78}materials/bloodpool/HFMaterials/051.emat","{4A39EAF1F1D5E277}materials/bloodpool/HFMaterials/052.emat","{BE31AD69FC088A03}materials/bloodpool/HFMaterials/053.emat","{F7E9B8768ECEFE69}materials/bloodpool/HFMaterials/054.emat","{03E1FFEE8313961D}materials/bloodpool/HFMaterials/055.emat","{5D09D6AD3C9E1812}materials/bloodpool/HFMaterials/056.emat","{A901913531437066}materials/bloodpool/HFMaterials/057.emat","{CEB9FC93D912F0C6}materials/bloodpool/HFMaterials/058.emat","{3AB1BB0BD4CF98B2}materials/bloodpool/HFMaterials/059.emat","{EA7CD467F595F78B}materials/bloodpool/HFMaterials/060.emat","{1E7493FFF8489FFF}materials/bloodpool/HFMaterials/061.emat","{409CBABC47C511F0}materials/bloodpool/HFMaterials/062.emat","{B494FD244A187984}materials/bloodpool/HFMaterials/063.emat","{FD4CE83B38DE0DEE}materials/bloodpool/HFMaterials/064.emat","{0944AFA33503659A}materials/bloodpool/HFMaterials/065.emat","{57AC86E08A8EEB95}materials/bloodpool/HFMaterials/066.emat","{A3A4C178875383E1}materials/bloodpool/HFMaterials/067.emat","{C41CACDE6F020341}materials/bloodpool/HFMaterials/068.emat","{3014EB4662DF6B35}materials/bloodpool/HFMaterials/069.emat","{2DB044FA00C3B487}materials/bloodpool/HFMaterials/070.emat","{D9B803620D1EDCF3}materials/bloodpool/HFMaterials/071.emat","{87502A21B29352FC}materials/bloodpool/HFMaterials/072.emat","{73586DB9BF4E3A88}materials/bloodpool/HFMaterials/073.emat","{3A8078A6CD884EE2}materials/bloodpool/HFMaterials/074.emat","{CE883F3EC0552696}materials/bloodpool/HFMaterials/075.emat","{9060167D7FD8A899}materials/bloodpool/HFMaterials/076.emat","{646851E57205C0ED}materials/bloodpool/HFMaterials/077.emat","{03D03C439A54404D}materials/bloodpool/HFMaterials/078.emat","{F7D87BDB97892839}materials/bloodpool/HFMaterials/079.emat","{0D8055816E90891C}materials/bloodpool/HFMaterials/080.emat","{F9881219634DE168}materials/bloodpool/HFMaterials/081.emat","{A7603B5ADCC06F67}materials/bloodpool/HFMaterials/082.emat","{53687CC2D11D0713}materials/bloodpool/HFMaterials/083.emat","{1AB069DDA3DB7379}materials/bloodpool/HFMaterials/084.emat","{EEB82E45AE061B0D}materials/bloodpool/HFMaterials/085.emat","{B0500706118B9502}materials/bloodpool/HFMaterials/086.emat","{4458409E1C56FD76}materials/bloodpool/HFMaterials/087.emat","{23E02D38F4077DD6}materials/bloodpool/HFMaterials/088.emat","{D7E86AA0F9DA15A2}materials/bloodpool/HFMaterials/089.emat","{CA4CC51C9BC6CA10}materials/bloodpool/HFMaterials/090.emat","{3E448284961BA264}materials/bloodpool/HFMaterials/091.emat","{60ACABC729962C6B}materials/bloodpool/HFMaterials/092.emat","{94A4EC5F244B441F}materials/bloodpool/HFMaterials/093.emat","{DD7CF940568D3075}materials/bloodpool/HFMaterials/094.emat","{2974BED85B505801}materials/bloodpool/HFMaterials/095.emat","{779C979BE4DDD60E}materials/bloodpool/HFMaterials/096.emat","{8394D003E900BE7A}materials/bloodpool/HFMaterials/097.emat","{E42CBDA501513EDA}materials/bloodpool/HFMaterials/098.emat","{1024FA3D0C8C56AE}materials/bloodpool/HFMaterials/099.emat","{917B4AA5ACD5FE0D}materials/bloodpool/HFMaterials/100.emat","{65730D3DA1089679}materials/bloodpool/HFMaterials/101.emat","{3B9B247E1E851876}materials/bloodpool/HFMaterials/102.emat","{CF9363E613587002}materials/bloodpool/HFMaterials/103.emat","{864B76F9619E0468}materials/bloodpool/HFMaterials/104.emat","{724331616C436C1C}materials/bloodpool/HFMaterials/105.emat","{2CAB1822D3CEE213}materials/bloodpool/HFMaterials/106.emat","{D8A35FBADE138A67}materials/bloodpool/HFMaterials/107.emat","{BF1B321C36420AC7}materials/bloodpool/HFMaterials/108.emat","{4B1375843B9F62B3}materials/bloodpool/HFMaterials/109.emat","{56B7DA385983BD01}materials/bloodpool/HFMaterials/110.emat","{A2BF9DA0545ED575}materials/bloodpool/HFMaterials/111.emat","{FC57B4E3EBD35B7A}materials/bloodpool/HFMaterials/112.emat","{085FF37BE60E330E}materials/bloodpool/HFMaterials/113.emat","{4187E66494C84764}materials/bloodpool/HFMaterials/114.emat","{B58FA1FC99152F10}materials/bloodpool/HFMaterials/115.emat","{EB6788BF2698A11F}materials/bloodpool/HFMaterials/116.emat","{1F6FCF272B45C96B}materials/bloodpool/HFMaterials/117.emat","{78D7A281C31449CB}materials/bloodpool/HFMaterials/118.emat","{8CDFE519CEC921BF}materials/bloodpool/HFMaterials/119.emat","{5C128A75EF934E86}materials/bloodpool/HFMaterials/120.emat","{A81ACDEDE24E26F2}materials/bloodpool/HFMaterials/121.emat","{F6F2E4AE5DC3A8FD}materials/bloodpool/HFMaterials/122.emat","{02FAA336501EC089}materials/bloodpool/HFMaterials/123.emat","{4B22B62922D8B4E3}materials/bloodpool/HFMaterials/124.emat","{BF2AF1B12F05DC97}materials/bloodpool/HFMaterials/125.emat","{E1C2D8F290885298}materials/bloodpool/HFMaterials/126.emat","{15CA9F6A9D553AEC}materials/bloodpool/HFMaterials/127.emat","{7272F2CC7504BA4C}materials/bloodpool/HFMaterials/128.emat","{867AB55478D9D238}materials/bloodpool/HFMaterials/129.emat","{9BDE1AE81AC50D8A}materials/bloodpool/HFMaterials/130.emat","{6FD65D70171865FE}materials/bloodpool/HFMaterials/131.emat","{313E7433A895EBF1}materials/bloodpool/HFMaterials/132.emat","{C53633ABA5488385}materials/bloodpool/HFMaterials/133.emat","{8CEE26B4D78EF7EF}materials/bloodpool/HFMaterials/134.emat","{78E6612CDA539F9B}materials/bloodpool/HFMaterials/135.emat","{260E486F65DE1194}materials/bloodpool/HFMaterials/136.emat","{D2060FF7680379E0}materials/bloodpool/HFMaterials/137.emat","{B5BE62518052F940}materials/bloodpool/HFMaterials/138.emat","{41B625C98D8F9134}materials/bloodpool/HFMaterials/139.emat","{49582AEE83B2A988}materials/bloodpool/HFMaterials/140.emat","{BD506D768E6FC1FC}materials/bloodpool/HFMaterials/141.emat","{E3B8443531E24FF3}materials/bloodpool/HFMaterials/142.emat","{17B003AD3C3F2787}materials/bloodpool/HFMaterials/143.emat","{5E6816B24EF953ED}materials/bloodpool/HFMaterials/144.emat","{AA60512A43243B99}materials/bloodpool/HFMaterials/145.emat","{F4887869FCA9B596}materials/bloodpool/HFMaterials/146.emat","{00803FF1F174DDE2}materials/bloodpool/HFMaterials/147.emat"});
		animationMaterials.Insert(EDecalType.GENERIC_SPLATTER, {"{00F6BBB6682F552B}materials/wall_splatter/000.emat","{F4FEFC2E65F23D5F}materials/wall_splatter/001.emat","{AA16D56DDA7FB350}materials/wall_splatter/002.emat","{5E1E92F5D7A2DB24}materials/wall_splatter/003.emat","{17C687EAA564AF4E}materials/wall_splatter/004.emat","{E3CEC072A8B9C73A}materials/wall_splatter/005.emat","{BD26E93117344935}materials/wall_splatter/006.emat","{492EAEA91AE92141}materials/wall_splatter/007.emat","{2E96C30FF2B8A1E1}materials/wall_splatter/008.emat","{DA9E8497FF65C995}materials/wall_splatter/009.emat","{C73A2B2B9D791627}materials/wall_splatter/010.emat","{33326CB390A47E53}materials/wall_splatter/011.emat","{6DDA45F02F29F05C}materials/wall_splatter/012.emat","{99D2026822F49828}materials/wall_splatter/013.emat","{D00A17775032EC42}materials/wall_splatter/014.emat","{240250EF5DEF8436}materials/wall_splatter/015.emat","{7AEA79ACE2620A39}materials/wall_splatter/016.emat","{8EE23E34EFBF624D}materials/wall_splatter/017.emat","{E95A539207EEE2ED}materials/wall_splatter/018.emat","{1D52140A0A338A99}materials/wall_splatter/019.emat","{CD9F7B662B69E5A0}materials/wall_splatter/020.emat","{39973CFE26B48DD4}materials/wall_splatter/021.emat","{677F15BD993903DB}materials/wall_splatter/022.emat","{9377522594E46BAF}materials/wall_splatter/023.emat","{DAAF473AE6221FC5}materials/wall_splatter/024.emat","{2EA700A2EBFF77B1}materials/wall_splatter/025.emat","{704F29E15472F9BE}materials/wall_splatter/026.emat","{84476E7959AF91CA}materials/wall_splatter/027.emat","{E3FF03DFB1FE116A}materials/wall_splatter/028.emat","{17F74447BC23791E}materials/wall_splatter/029.emat","{0A53EBFBDE3FA6AC}materials/wall_splatter/030.emat","{FE5BAC63D3E2CED8}materials/wall_splatter/031.emat","{A0B385206C6F40D7}materials/wall_splatter/032.emat","{54BBC2B861B228A3}materials/wall_splatter/033.emat","{1D63D7A713745CC9}materials/wall_splatter/034.emat","{E96B903F1EA934BD}materials/wall_splatter/035.emat","{B783B97CA124BAB2}materials/wall_splatter/036.emat","{438BFEE4ACF9D2C6}materials/wall_splatter/037.emat","{2433934244A85266}materials/wall_splatter/038.emat","{D03BD4DA49753A12}materials/wall_splatter/039.emat","{D8D5DBFD474802AE}materials/wall_splatter/040.emat","{2CDD9C654A956ADA}materials/wall_splatter/041.emat","{7235B526F518E4D5}materials/wall_splatter/042.emat","{863DF2BEF8C58CA1}materials/wall_splatter/043.emat","{CFE5E7A18A03F8CB}materials/wall_splatter/044.emat","{3BEDA03987DE90BF}materials/wall_splatter/045.emat","{6505897A38531EB0}materials/wall_splatter/046.emat","{910DCEE2358E76C4}materials/wall_splatter/047.emat","{F6B5A344DDDFF664}materials/wall_splatter/048.emat","{02BDE4DCD0029E10}materials/wall_splatter/049.emat","{1F194B60B21E41A2}materials/wall_splatter/050.emat","{EB110CF8BFC329D6}materials/wall_splatter/051.emat","{B5F925BB004EA7D9}materials/wall_splatter/052.emat","{41F162230D93CFAD}materials/wall_splatter/053.emat","{0829773C7F55BBC7}materials/wall_splatter/054.emat","{FC2130A47288D3B3}materials/wall_splatter/055.emat","{A2C919E7CD055DBC}materials/wall_splatter/056.emat","{56C15E7FC0D835C8}materials/wall_splatter/057.emat","{317933D92889B568}materials/wall_splatter/058.emat","{C57174412554DD1C}materials/wall_splatter/059.emat","{15BC1B2D040EB225}materials/wall_splatter/060.emat","{E1B45CB509D3DA51}materials/wall_splatter/061.emat","{BF5C75F6B65E545E}materials/wall_splatter/062.emat","{4B54326EBB833C2A}materials/wall_splatter/063.emat"});
		
		
		instance = this;
		
		
		//Print(ProceduralTexture.GenerateAlphaTexture());
		
		
		
		
		
		
		
		
		
		
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
		
		//GetGame().GetCallqueue().Tick(timeSlice);		//Maybe?
		
		
		if (decalsSpawned.Count() > 0)
		{
			currentTime += timeSlice;
		
			
			
			//set dynamic stuff here 
			//ablSettings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);
			//waitTimeBetweenFrames = ablSettings.Get("waitTimeBetweenFrames").ToFloat();
				
			
			
			
			if (currentTime > waitTimeBetweenFrames)
			{
				SpawnAnimatedFrames();
				currentTime = 0;
				settings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);

				waitTimeBetweenFrames = settings.Get("waitTimeBetweenFrames").ToFloat();

			}
		}
		else
			return;

	}
	
	
	
	//void SetupNewAnimation(int index, Decal dec, int frames, float rot, vector orig, vector proj, int si)
	void StartNewAnimation(IEntity character, vector hitPosition, vector hitDirection, EDecalType type, bool terrainOnly, float sizeModifier, int nodeId)
	{
		vector intersectionPosition;
		float distance = 2.0;
		TraceParam traceParam;
		vector origin;
		vector projection;
		array<ResourceName> tempFrames = animationMaterials.Get(type);
		
	
		if (terrainOnly)
		{
			traceParam = GetSurfaceIntersection(character, m_world, hitPosition, Vector(0, -1, 0), distance,TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
			
			//TEST differnet origin 
			vector mat[4];

			if (type == EDecalType.BLOODPOOL && character.GetBoneMatrix(nodeId, mat))
			{
				vector pos = character.CoordToParent(mat[3]);
				pos[2] = pos[2] + 0.5;
				origin = pos;
				projection = -traceParam.TraceNorm;
			}
			else
			{
				origin = character.GetOrigin() + Vector(0, 2.0 / 4, 0);			
		 		projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);

			}

		}
		else
		{
			traceParam = GetSurfaceIntersection(character, m_world, hitPosition, hitDirection, distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
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
			float size = Math.RandomFloatInclusive(1.0, 1.0 + sizeModifier);		//Doesn't seem random.... 
			float angle = character.GetYawPitchRoll()[2];
			
			//Math.RandomFloatInclusive(-angleModifier, angleModifier) * Math.DEG2RAD;
			
			Decal tmpDecal = m_world.CreateDecal(traceParam.TraceEnt, origin, projection, nearClip, farClip, angle, size, 1, tempFrames[0], -1, materialColor);
			

			// try to insert it into the decalsSpawned map 
			
			int index = Math.RandomInt(-10000, 10000);
			
			while(decalsSpawned.Get(index))
				index = Math.RandomInt(-10000, 10000);
			
			
			DecalInformation tmpDecalInformation = new DecalInformation(tmpDecal, type, 1, traceParam, hitPosition, hitDirection, origin, projection, size, angle, Math.RandomFloatInclusive(1, 1.3), terrainOnly); 
			decalsSpawned.Insert(index, tmpDecalInformation);	
		}

	}
	
	
	void SpawnAnimatedFrames()
	{
		float distance = 2.0;

		foreach(int index, DecalInformation dInfo  : decalsSpawned)
		{
			Decal d = dInfo.decal;
			int currentFrame = dInfo.currentFrame;
			array<ResourceName> tempFrames = animationMaterials.Get(dInfo.type);
			
			
			// DEBUG 
			
			//Print("Index: " + index);
			//Print("Current Frame: " + currentFrame);
			//Print("_______________");
			
			
			if (currentFrame < tempFrames.Count())
			{
				if (d)
					m_world.RemoveDecal(d);
					
				TraceParam traceParam = dInfo.traceParam;
				
				if (traceParam.TraceEnt) // spawn splatter below character
				{
					
					
					Material tmp = Material.GetOrLoadMaterial(tempFrames[currentFrame], 0);
					//tmp.SetParam("AlphaMul", 1.25);
					
					float modifiedAlphaMul = dInfo.currentAlphaMul + Math.RandomFloat(0.0001, 0.02);
					//float modifiedAlphaTest = dInfo.currentAlpha + Math.RandomFloat(0.0001, 0.02);

					
					//tmp.SetParam("AlphaMul", modifiedAlphaMul);
					//tmpSetParam("AlphaTest", modifiedAlphaTest
					
					dInfo.currentAlphaMul = modifiedAlphaMul; 
					//Print(modifiedAlphaMul);
					
					tmp.SetParam("GBufferNormal", 1);
					tmp.SetParam("NormalCombinePower",1.3 + Math.RandomFloat(-0.1, 0.1));
					Decal newDecal = m_world.CreateDecal(traceParam.TraceEnt, dInfo.originPosition, dInfo.projectionDirection, nearClip, farClip, dInfo.rotation, dInfo.size, 1, tempFrames[currentFrame], -1, materialColor);
					
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
	static  TraceParam GetSurfaceIntersection(IEntity owner,World world,vector origin,vector direction, float distance, int flags, out vector intersectionPosition)
	{
		auto param = new TraceParam();
  		param.Start = origin;
  		param.End = origin + direction * distance;
  		param.Flags = flags;
  		param.Exclude = owner;
		float intersectionDistance = world.TraceMove(param, NULL) * distance;
		intersectionPosition = origin + (direction * intersectionDistance);
		return param;
	}
	
	
	
}





class ProceduralTexture
{
	//perlin? 
	
	
	static array<float> GenerateAlphaTexture()
	{
		float t = Math.PerlinNoise(10);		//boh 
		
		float height = 256;
		float width = 256;
		
		
		//array test[256][256] = new array[256][256]();
		
		
		
		
		
		array<float> matrix = new array<float>();
		
		//fuck it
		
		//array<array> matrix = new array<array>();
		//
		//array<float> row = new array<float>();
		
		
		//not sure if its doable
		
		for (int i = 0; i < width * height; i++)
		{
			float nx;
			float perlin = Math.PerlinNoise(Math.RandomFloat(-100,100));
		
			matrix.Insert(perlin);
			
			//matrix.Insert(new array<float>());
			//row.Clear();		//reset
			
			//matrix.Set(y, new array<float>());
			
			
			
			//for (int x = 0; x < width; x++)
			//{
		  //		float nx = Math.RandomFloat(-100,100);
		//		float perlin = Math.PerlinNoise(nx);
			//	
			//	matrix.Get(y).Insert(perlin);
				//row.Insert(perlin);// = Math.PerlinNoise(nx);
		
		//	}
			
		
		
			//matrix.Insert(row);
		
		}
		
		return matrix;

		
		/*
		
		//array<vector>> values = new array<vector>(); 
		// jesus, a loop 
		for (int y = 0; y < height; y++) 
		{
 			 for (int x = 0; x < width; x++) 
			{      
    			float nx = x/width - 0.5, ny = y/height - 0.5;
    			test[y][x] =  Math.PerlinNoise(nx);
 			}
		}
		*/
	
	}

}

class DecalInformation
{
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
	float currentAlphaMul;
	
	bool terrainOnly;
	
	void DecalInformation( Decal d, EDecalType t, int cf, TraceParam tp, vector hp, vector hd, vector op, vector pd, float s, float r, float cam, bool to)
	{
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
		currentAlphaMul = cam;
		terrainOnly = to;
	}
}

enum EDecalType
{
	BLOODPOOL,
	GENERIC_SPLATTER
}





//move this away 


class CleaningAction 
{

	void SomeInitMethod()
	{
	}
	
	protected void YourDownCallback(float value, EActionTrigger trigger)
	{
	
}
}