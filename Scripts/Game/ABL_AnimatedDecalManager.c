class ABL_AnimatedDecalManagerClass : GenericEntityClass
{}



//todo implement weapon cleaning 



class ABL_AnimatedDecalManager : GenericEntity
{
	
	ref map<EDecalType, ref array<ResourceName>> materialsMap;
	ref map<int, ref DecalInformation> decalsSpawned;
	
	ref map<int, ref DecalInformation> wallSplattersSpawned;			//must be max 1-2 i guess?
	// won't work. we'd need to save the time and hten compare it to the current one that's gonna be spawned 
	
	
	
	
	ref array<ResourceName> alphaNoise;
	const string ABL_MOD_ID = "59951797A291CA02";				//it's probably possible to get this in a better way but ok

	// 1) must be initialized one time 
	// 2) each char will relate to this.
	//3) should be spawned at runtime, maybe first char that spawns actualy spawn this. So for now let's just usemake it really stupid and get the entity from the world
	

	static ABL_AnimatedDecalManager instance;
	
	
	private World m_world;
	int materialColor;	//todo make this dynamic 
	float waitTimeBetweenFrames;
	float currentTime;

	
	const float nearClip = 0.0;
	const float farClip = 5;
	
	
	
	ref map<string, string> settings;
	ref map<string, string> waitBetweenFrames
	
	
	
	
	float lastWallSplatterSpawnedTime;
	
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
		materialsMap = new map<EDecalType, ref array<ResourceName>>();
	
		materialsMap.Insert(EDecalType.BLOODPOOL, {"{86CF08622B53AC10}materials/bloodpool/001.emat","{D827212194DE221F}materials/bloodpool/002.emat","{2C2F66B999034A6B}materials/bloodpool/003.emat","{65F773A6EBC53E01}materials/bloodpool/004.emat","{91FF343EE6185675}materials/bloodpool/005.emat","{CF171D7D5995D87A}materials/bloodpool/006.emat","{3B1F5AE55448B00E}materials/bloodpool/007.emat","{5CA73743BC1930AE}materials/bloodpool/008.emat","{A8AF70DBB1C458DA}materials/bloodpool/009.emat","{B50BDF67D3D88768}materials/bloodpool/010.emat","{410398FFDE05EF1C}materials/bloodpool/011.emat","{1FEBB1BC61886113}materials/bloodpool/012.emat","{EBE3F6246C550967}materials/bloodpool/013.emat","{A23BE33B1E937D0D}materials/bloodpool/014.emat","{5633A4A3134E1579}materials/bloodpool/015.emat","{08DB8DE0ACC39B76}materials/bloodpool/016.emat","{FCD3CA78A11EF302}materials/bloodpool/017.emat","{9B6BA7DE494F73A2}materials/bloodpool/018.emat","{6F63E04644921BD6}materials/bloodpool/019.emat","{BFAE8F2A65C874EF}materials/bloodpool/020.emat","{4BA6C8B268151C9B}materials/bloodpool/021.emat","{154EE1F1D7989294}materials/bloodpool/022.emat","{E146A669DA45FAE0}materials/bloodpool/023.emat","{A89EB376A8838E8A}materials/bloodpool/024.emat","{5C96F4EEA55EE6FE}materials/bloodpool/025.emat","{027EDDAD1AD368F1}materials/bloodpool/026.emat","{F6769A35170E0085}materials/bloodpool/027.emat","{91CEF793FF5F8025}materials/bloodpool/028.emat","{65C6B00BF282E851}materials/bloodpool/029.emat","{78621FB7909E37E3}materials/bloodpool/030.emat","{8C6A582F9D435F97}materials/bloodpool/031.emat","{D282716C22CED198}materials/bloodpool/032.emat","{268A36F42F13B9EC}materials/bloodpool/033.emat","{6F5223EB5DD5CD86}materials/bloodpool/034.emat","{9B5A64735008A5F2}materials/bloodpool/035.emat","{C5B24D30EF852BFD}materials/bloodpool/036.emat","{31BA0AA8E2584389}materials/bloodpool/037.emat","{5602670E0A09C329}materials/bloodpool/038.emat","{A20A209607D4AB5D}materials/bloodpool/039.emat","{AAE42FB109E993E1}materials/bloodpool/040.emat","{5EEC68290434FB95}materials/bloodpool/041.emat","{0004416ABBB9759A}materials/bloodpool/042.emat","{F40C06F2B6641DEE}materials/bloodpool/043.emat","{BDD413EDC4A26984}materials/bloodpool/044.emat","{49DC5475C97F01F0}materials/bloodpool/045.emat","{17347D3676F28FFF}materials/bloodpool/046.emat","{E33C3AAE7B2FE78B}materials/bloodpool/047.emat","{84845708937E672B}materials/bloodpool/048.emat","{708C10909EA30F5F}materials/bloodpool/049.emat","{6D28BF2CFCBFD0ED}materials/bloodpool/050.emat","{9920F8B4F162B899}materials/bloodpool/051.emat","{C7C8D1F74EEF3696}materials/bloodpool/052.emat","{33C0966F43325EE2}materials/bloodpool/053.emat","{7A18837031F42A88}materials/bloodpool/054.emat","{8E10C4E83C2942FC}materials/bloodpool/055.emat","{D0F8EDAB83A4CCF3}materials/bloodpool/056.emat","{24F0AA338E79A487}materials/bloodpool/057.emat","{4348C79566282427}materials/bloodpool/058.emat","{B740800D6BF54C53}materials/bloodpool/059.emat","{678DEF614AAF236A}materials/bloodpool/060.emat","{9385A8F947724B1E}materials/bloodpool/061.emat","{CD6D81BAF8FFC511}materials/bloodpool/062.emat","{3965C622F522AD65}materials/bloodpool/063.emat","{70BDD33D87E4D90F}materials/bloodpool/064.emat","{84B594A58A39B17B}materials/bloodpool/065.emat","{DA5DBDE635B43F74}materials/bloodpool/066.emat","{2E55FA7E38695700}materials/bloodpool/067.emat","{49ED97D8D038D7A0}materials/bloodpool/068.emat","{BDE5D040DDE5BFD4}materials/bloodpool/069.emat","{A0417FFCBFF96066}materials/bloodpool/070.emat","{54493864B2240812}materials/bloodpool/071.emat","{0AA111270DA9861D}materials/bloodpool/072.emat","{FEA956BF0074EE69}materials/bloodpool/073.emat","{B77143A072B29A03}materials/bloodpool/074.emat","{437904387F6FF277}materials/bloodpool/075.emat","{1D912D7BC0E27C78}materials/bloodpool/076.emat","{E9996AE3CD3F140C}materials/bloodpool/077.emat","{8E210745256E94AC}materials/bloodpool/078.emat","{7A2940DD28B3FCD8}materials/bloodpool/079.emat","{80716E87D1AA5DFD}materials/bloodpool/080.emat","{7479291FDC773589}materials/bloodpool/081.emat","{2A91005C63FABB86}materials/bloodpool/082.emat","{DE9947C46E27D3F2}materials/bloodpool/083.emat","{974152DB1CE1A798}materials/bloodpool/084.emat","{63491543113CCFEC}materials/bloodpool/085.emat","{3DA13C00AEB141E3}materials/bloodpool/086.emat","{C9A97B98A36C2997}materials/bloodpool/087.emat","{AE11163E4B3DA937}materials/bloodpool/088.emat","{5A1951A646E0C143}materials/bloodpool/089.emat","{47BDFE1A24FC1EF1}materials/bloodpool/090.emat","{B3B5B98229217685}materials/bloodpool/091.emat","{ED5D90C196ACF88A}materials/bloodpool/092.emat","{1955D7599B7190FE}materials/bloodpool/093.emat","{508DC246E9B7E494}materials/bloodpool/094.emat","{A48585DEE46A8CE0}materials/bloodpool/095.emat","{FA6DAC9D5BE702EF}materials/bloodpool/096.emat","{0E65EB05563A6A9B}materials/bloodpool/097.emat","{69DD86A3BE6BEA3B}materials/bloodpool/098.emat","{9DD5C13BB3B6824F}materials/bloodpool/099.emat","{1C8A71A313EF2AEC}materials/bloodpool/100.emat","{E882363B1E324298}materials/bloodpool/101.emat","{B66A1F78A1BFCC97}materials/bloodpool/102.emat","{426258E0AC62A4E3}materials/bloodpool/103.emat","{0BBA4DFFDEA4D089}materials/bloodpool/104.emat","{FFB20A67D379B8FD}materials/bloodpool/105.emat","{A15A23246CF436F2}materials/bloodpool/106.emat","{555264BC61295E86}materials/bloodpool/107.emat","{32EA091A8978DE26}materials/bloodpool/108.emat","{C6E24E8284A5B652}materials/bloodpool/109.emat","{DB46E13EE6B969E0}materials/bloodpool/110.emat","{2F4EA6A6EB640194}materials/bloodpool/111.emat","{71A68FE554E98F9B}materials/bloodpool/112.emat","{85AEC87D5934E7EF}materials/bloodpool/113.emat","{CC76DD622BF29385}materials/bloodpool/114.emat","{387E9AFA262FFBF1}materials/bloodpool/115.emat","{6696B3B999A275FE}materials/bloodpool/116.emat","{929EF421947F1D8A}materials/bloodpool/117.emat","{F52699877C2E9D2A}materials/bloodpool/118.emat","{012EDE1F71F3F55E}materials/bloodpool/119.emat","{D1E3B17350A99A67}materials/bloodpool/120.emat","{25EBF6EB5D74F213}materials/bloodpool/121.emat","{7B03DFA8E2F97C1C}materials/bloodpool/122.emat","{8F0B9830EF241468}materials/bloodpool/123.emat","{C6D38D2F9DE26002}materials/bloodpool/124.emat","{32DBCAB7903F0876}materials/bloodpool/125.emat","{6C33E3F42FB28679}materials/bloodpool/126.emat","{983BA46C226FEE0D}materials/bloodpool/127.emat","{FF83C9CACA3E6EAD}materials/bloodpool/128.emat","{0B8B8E52C7E306D9}materials/bloodpool/129.emat","{162F21EEA5FFD96B}materials/bloodpool/130.emat","{E2276676A822B11F}materials/bloodpool/131.emat","{BCCF4F3517AF3F10}materials/bloodpool/132.emat","{48C708AD1A725764}materials/bloodpool/133.emat","{011F1DB268B4230E}materials/bloodpool/134.emat","{F5175A2A65694B7A}materials/bloodpool/135.emat","{ABFF7369DAE4C575}materials/bloodpool/136.emat","{5FF734F1D739AD01}materials/bloodpool/137.emat","{384F59573F682DA1}materials/bloodpool/138.emat","{CC471ECF32B545D5}materials/bloodpool/139.emat","{C4A911E83C887D69}materials/bloodpool/140.emat","{30A156703155151D}materials/bloodpool/141.emat","{6E497F338ED89B12}materials/bloodpool/142.emat","{9A4138AB8305F366}materials/bloodpool/143.emat","{D3992DB4F1C3870C}materials/bloodpool/144.emat","{27916A2CFC1EEF78}materials/bloodpool/145.emat","{7979436F43936177}materials/bloodpool/146.emat","{8D7104F74E4E0903}materials/bloodpool/147.emat","{EAC96951A61F89A3}materials/bloodpool/148.emat","{1EC12EC9ABC2E1D7}materials/bloodpool/149.emat","{03658175C9DE3E65}materials/bloodpool/150.emat","{F76DC6EDC4035611}materials/bloodpool/151.emat","{A985EFAE7B8ED81E}materials/bloodpool/152.emat","{5D8DA8367653B06A}materials/bloodpool/153.emat","{1455BD290495C400}materials/bloodpool/154.emat","{E05DFAB10948AC74}materials/bloodpool/155.emat","{BEB5D3F2B6C5227B}materials/bloodpool/156.emat","{4ABD946ABB184A0F}materials/bloodpool/157.emat","{2D05F9CC5349CAAF}materials/bloodpool/158.emat","{D90DBE545E94A2DB}materials/bloodpool/159.emat","{09C0D1387FCECDE2}materials/bloodpool/160.emat","{FDC896A07213A596}materials/bloodpool/161.emat","{A320BFE3CD9E2B99}materials/bloodpool/162.emat","{5728F87BC04343ED}materials/bloodpool/163.emat","{1EF0ED64B2853787}materials/bloodpool/164.emat","{EAF8AAFCBF585FF3}materials/bloodpool/165.emat","{B41083BF00D5D1FC}materials/bloodpool/166.emat","{4018C4270D08B988}materials/bloodpool/167.emat","{27A0A981E5593928}materials/bloodpool/168.emat","{D3A8EE19E884515C}materials/bloodpool/169.emat","{CE0C41A58A988EEE}materials/bloodpool/170.emat","{3A04063D8745E69A}materials/bloodpool/171.emat","{64EC2F7E38C86895}materials/bloodpool/172.emat","{90E468E6351500E1}materials/bloodpool/173.emat","{D93C7DF947D3748B}materials/bloodpool/174.emat","{2D343A614A0E1CFF}materials/bloodpool/175.emat","{73DC1322F58392F0}materials/bloodpool/176.emat","{87D454BAF85EFA84}materials/bloodpool/177.emat","{E06C391C100F7A24}materials/bloodpool/178.emat","{14647E841DD21250}materials/bloodpool/179.emat","{EE3C50DEE4CBB375}materials/bloodpool/180.emat","{1A341746E916DB01}materials/bloodpool/181.emat","{44DC3E05569B550E}materials/bloodpool/182.emat","{B0D4799D5B463D7A}materials/bloodpool/183.emat","{F90C6C8229804910}materials/bloodpool/184.emat","{0D042B1A245D2164}materials/bloodpool/185.emat","{53EC02599BD0AF6B}materials/bloodpool/186.emat","{A7E445C1960DC71F}materials/bloodpool/187.emat","{C05C28677E5C47BF}materials/bloodpool/188.emat","{34546FFF73812FCB}materials/bloodpool/189.emat","{29F0C043119DF079}materials/bloodpool/190.emat","{DDF887DB1C40980D}materials/bloodpool/191.emat","{8310AE98A3CD1602}materials/bloodpool/192.emat","{7718E900AE107E76}materials/bloodpool/193.emat","{3EC0FC1FDCD60A1C}materials/bloodpool/194.emat","{CAC8BB87D10B6268}materials/bloodpool/195.emat","{942092C46E86EC67}materials/bloodpool/196.emat","{6028D55C635B8413}materials/bloodpool/197.emat","{0790B8FA8B0A04B3}materials/bloodpool/198.emat","{F398FF6286D76CC7}materials/bloodpool/199.emat"});
		materialsMap.Insert(EDecalType.WALLSPLATTER, {"{85A421FD8938D6B2}materials/wall_splatter_2/0.emat","{71AC666584E5BEC6}materials/wall_splatter_2/1.emat","{2F444F263B6830C9}materials/wall_splatter_2/2.emat","{DB4C08BE36B558BD}materials/wall_splatter_2/3.emat","{92941DA144732CD7}materials/wall_splatter_2/4.emat","{669C5A3949AE44A3}materials/wall_splatter_2/5.emat","{3874737AF623CAAC}materials/wall_splatter_2/6.emat","{CC7C34E2FBFEA2D8}materials/wall_splatter_2/7.emat","{ABC4594413AF2278}materials/wall_splatter_2/8.emat","{5FCC1EDC1E724A0C}materials/wall_splatter_2/9.emat","{5B2DD19AD7874B53}materials/wall_splatter_2/10.emat","{AF259602DA5A2327}materials/wall_splatter_2/11.emat","{F1CDBF4165D7AD28}materials/wall_splatter_2/12.emat","{05C5F8D9680AC55C}materials/wall_splatter_2/13.emat","{4C1DEDC61ACCB136}materials/wall_splatter_2/14.emat","{B815AA5E1711D942}materials/wall_splatter_2/15.emat","{E6FD831DA89C574D}materials/wall_splatter_2/16.emat","{12F5C485A5413F39}materials/wall_splatter_2/17.emat","{754DA9234D10BF99}materials/wall_splatter_2/18.emat","{8145EEBB40CDD7ED}materials/wall_splatter_2/19.emat","{518881D76197B8D4}materials/wall_splatter_2/20.emat","{A580C64F6C4AD0A0}materials/wall_splatter_2/21.emat","{FB68EF0CD3C75EAF}materials/wall_splatter_2/22.emat","{0F60A894DE1A36DB}materials/wall_splatter_2/23.emat","{46B8BD8BACDC42B1}materials/wall_splatter_2/24.emat","{B2B0FA13A1012AC5}materials/wall_splatter_2/25.emat","{EC58D3501E8CA4CA}materials/wall_splatter_2/26.emat","{185094C81351CCBE}materials/wall_splatter_2/27.emat","{7FE8F96EFB004C1E}materials/wall_splatter_2/28.emat","{8BE0BEF6F6DD246A}materials/wall_splatter_2/29.emat","{9644114A94C1FBD8}materials/wall_splatter_2/30.emat","{624C56D2991C93AC}materials/wall_splatter_2/31.emat","{3CA47F9126911DA3}materials/wall_splatter_2/32.emat","{C8AC38092B4C75D7}materials/wall_splatter_2/33.emat","{81742D16598A01BD}materials/wall_splatter_2/34.emat","{757C6A8E545769C9}materials/wall_splatter_2/35.emat","{2B9443CDEBDAE7C6}materials/wall_splatter_2/36.emat","{DF9C0455E6078FB2}materials/wall_splatter_2/37.emat","{B82469F30E560F12}materials/wall_splatter_2/38.emat","{4C2C2E6B038B6766}materials/wall_splatter_2/39.emat","{44C2214C0DB65FDA}materials/wall_splatter_2/40.emat","{B0CA66D4006B37AE}materials/wall_splatter_2/41.emat","{EE224F97BFE6B9A1}materials/wall_splatter_2/42.emat","{1A2A080FB23BD1D5}materials/wall_splatter_2/43.emat","{53F21D10C0FDA5BF}materials/wall_splatter_2/44.emat","{A7FA5A88CD20CDCB}materials/wall_splatter_2/45.emat","{F91273CB72AD43C4}materials/wall_splatter_2/46.emat","{0D1A34537F702BB0}materials/wall_splatter_2/47.emat","{6AA259F59721AB10}materials/wall_splatter_2/48.emat","{9EAA1E6D9AFCC364}materials/wall_splatter_2/49.emat","{830EB1D1F8E01CD6}materials/wall_splatter_2/50.emat","{7706F649F53D74A2}materials/wall_splatter_2/51.emat","{29EEDF0A4AB0FAAD}materials/wall_splatter_2/52.emat","{DDE69892476D92D9}materials/wall_splatter_2/53.emat","{943E8D8D35ABE6B3}materials/wall_splatter_2/54.emat","{6036CA1538768EC7}materials/wall_splatter_2/55.emat","{3EDEE35687FB00C8}materials/wall_splatter_2/56.emat","{CAD6A4CE8A2668BC}materials/wall_splatter_2/57.emat","{AD6EC9686277E81C}materials/wall_splatter_2/58.emat","{59668EF06FAA8068}materials/wall_splatter_2/59.emat","{89ABE19C4EF0EF51}materials/wall_splatter_2/60.emat","{7DA3A604432D8725}materials/wall_splatter_2/61.emat","{234B8F47FCA0092A}materials/wall_splatter_2/62.emat","{D743C8DFF17D615E}materials/wall_splatter_2/63.emat","{9E9BDDC083BB1534}materials/wall_splatter_2/64.emat","{6A939A588E667D40}materials/wall_splatter_2/65.emat","{347BB31B31EBF34F}materials/wall_splatter_2/66.emat","{C073F4833C369B3B}materials/wall_splatter_2/67.emat","{A7CB9925D4671B9B}materials/wall_splatter_2/68.emat","{53C3DEBDD9BA73EF}materials/wall_splatter_2/69.emat","{4E677101BBA6AC5D}materials/wall_splatter_2/70.emat","{BA6F3699B67BC429}materials/wall_splatter_2/71.emat","{E4871FDA09F64A26}materials/wall_splatter_2/72.emat","{108F5842042B2252}materials/wall_splatter_2/73.emat","{59574D5D76ED5638}materials/wall_splatter_2/74.emat","{AD5F0AC57B303E4C}materials/wall_splatter_2/75.emat","{F3B72386C4BDB043}materials/wall_splatter_2/76.emat","{07BF641EC960D837}materials/wall_splatter_2/77.emat","{600709B821315897}materials/wall_splatter_2/78.emat","{940F4E202CEC30E3}materials/wall_splatter_2/79.emat","{6E57607AD5F591C6}materials/wall_splatter_2/80.emat","{9A5F27E2D828F9B2}materials/wall_splatter_2/81.emat","{C4B70EA167A577BD}materials/wall_splatter_2/82.emat","{30BF49396A781FC9}materials/wall_splatter_2/83.emat","{79675C2618BE6BA3}materials/wall_splatter_2/84.emat","{8D6F1BBE156303D7}materials/wall_splatter_2/85.emat","{D38732FDAAEE8DD8}materials/wall_splatter_2/86.emat","{278F7565A733E5AC}materials/wall_splatter_2/87.emat","{403718C34F62650C}materials/wall_splatter_2/88.emat","{B43F5F5B42BF0D78}materials/wall_splatter_2/89.emat","{A99BF0E720A3D2CA}materials/wall_splatter_2/90.emat","{5D93B77F2D7EBABE}materials/wall_splatter_2/91.emat","{037B9E3C92F334B1}materials/wall_splatter_2/92.emat","{F773D9A49F2E5CC5}materials/wall_splatter_2/93.emat","{BEABCCBBEDE828AF}materials/wall_splatter_2/94.emat","{4AA38B23E03540DB}materials/wall_splatter_2/95.emat","{144BA2605FB8CED4}materials/wall_splatter_2/96.emat","{E043E5F85265A6A0}materials/wall_splatter_2/97.emat","{87FB885EBA342600}materials/wall_splatter_2/98.emat","{73F3CFC6B7E94E74}materials/wall_splatter_2/99.emat"});
		materialsMap.Insert(EDecalType.SINGLE_FRAME_GENERIC_SPLATTER, {"{B3196D0D8CB491D5}materials/ground_splatter/001.emat"});
		
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

		//if (wallSplattersSpawned.Count() > 0)
		//{		
		//}
		
		
		if (decalsSpawned.Count() > 0)
		{
			currentTime += timeSlice;
						
			
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
	
	
	void SpawnSingleFrame(IEntity character, World world, vector hitPosition, vector hitDirection)

	{
		
		
		array<ResourceName> resources = materialsMap.Get(EDecalType.SINGLE_FRAME_GENERIC_SPLATTER);
		int randomIndex = Math.RandomIntInclusive(0, resources.Count() - 1);
		ResourceName material = resources[randomIndex];
		
		vector intersectionPosition;
		vector mat[4];
		float distance = 2.0;
		TraceParam traceParam;
		vector origin;
		vector projection;
		
		
		
		vector correctedDirection = hitDirection;
		correctedDirection[1] = correctedDirection[1] - 1.5;
		
		//Print(hitPosition);
		//Print(correctedDirection);
		
		
		traceParam = GetSurfaceIntersection(character, world, hitPosition, correctedDirection, distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
			
		
		//this is wrong. we don't want to origin, we want the point of impact.
		origin = hitPosition + Vector(0, 2.0 / 4, 0);	
		projection = vector.Lerp(-traceParam.TraceNorm, correctedDirection, 0.2);

		if (traceParam.TraceEnt) // spawn splatter 
		{			
			float angle = Math.RandomFloatInclusive(-360, 360);
			float size = Math.RandomFloatInclusive(0.2, 0.8);

			Decal tmpDecal = world.CreateDecal(traceParam.TraceEnt, origin, projection, 0, 2, angle, size, 1, material, -1, Color.FromRGBA(128, 0, 0,255).PackToInt());

		}
	}
	
	//void SetupNewAnimation(int index, Decal dec, int frames, float rot, vector orig, vector proj, int si)
	void StartNewAnimation(IEntity character, vector hitPosition, vector hitDirection, EDecalType type, bool terrainOnly, float sizeModifier, int nodeId)
	{
		vector intersectionPosition;
		float distance = 2.0;
		float angle;
		TraceParam traceParam;
		vector origin;
		vector projection;
		array<ResourceName> tempFrames = materialsMap.Get(type);
		
		
		int traceFlags;
		
		if (terrainOnly)
			traceFlags = TraceFlags.WORLD;
		else 
			traceFlags = TraceFlags.WORLD | TraceFlags.ENTS;
		

		//TEST differnet origin 
		vector mat[4];
			
        // Setup variables here
		Material tmp;
        ResourceName chosenResource;
		int indexAlpha = -1;
		float size = 1;
		float alphaTestValue;		//default
		float alphaMulValue = 1;			//default starting point of mul
		settings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);			//refresh!

		switch(type)
		{
			
			case EDecalType.BLOODPOOL:
			{
					
				if (character.GetBoneMatrix(nodeId, mat))
				{
					traceParam = GetSurfaceIntersection(character, m_world, hitPosition, Vector(0, -1, 0), distance, traceFlags, intersectionPosition);
					vector pos = character.CoordToParent(mat[3]);
					pos[2] = pos[2];//+ 0.5;
					origin = pos;
					projection = -traceParam.TraceNorm;
					
					angle = 0;		//SelectBloodpoolAngle(origin);
					indexAlpha = Math.RandomIntInclusive(0, materialsMap.Get(EDecalType.BLOODPOOL).Count() - 1);			//todo make this dynamic
				    chosenResource = tempFrames[indexAlpha];
					size = settings.Get("bloodpoolSize").ToFloat();
					alphaMulValue = 0.55;
					alphaTestValue = 0.670;		//shouldn't decrease.

				}
				else 
				{
					//cant find bone, should never happen?
					
					//happens with grenades
					traceParam = GetSurfaceIntersection(character, m_world, hitPosition, Vector(0, -1, 0), distance, traceFlags, intersectionPosition);

					origin = character.GetOrigin() + Vector(0, 2.0 / 4, 0);			
		 			projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);
				}
			
				break;
			}
			case EDecalType.WALLSPLATTER:
			{

				traceParam = GetSurfaceIntersection(character, m_world, hitPosition, hitDirection, distance, traceFlags, intersectionPosition);
				angle = 0;
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
				
				
				
				indexAlpha = Math.RandomIntInclusive(0, materialsMap.Get(EDecalType.WALLSPLATTER).Count() - 1);			//todo make this dynamic

				
				
                chosenResource = tempFrames[indexAlpha];
				alphaMulValue = 1.4;
				alphaTestValue = 3;			//starting point

				size = settings.Get("wallsplatterSize").ToFloat();

				break;
			}
			
			
		}

		if (traceParam.TraceEnt) 
		{			
            tmp = Material.GetOrLoadMaterial(chosenResource, 0);
		    Decal tmpDecal = m_world.CreateDecal(traceParam.TraceEnt, origin, projection, nearClip, farClip, angle, size, 1, chosenResource, -1, materialColor);


			// try to insert it into the decalsSpawned map 
			int index = Math.RandomInt(-10000, 10000);
			while(decalsSpawned.Get(index))
				index = Math.RandomInt(-10000, 10000);



            DecalBaseInfo decalBaseInfo = new DecalBaseInfo(tmpDecal, type, 0, size, angle, 1);
            DecalPositionInfo decalPositionInfo = new DecalPositionInfo(traceParam, hitPosition, hitDirection, origin, projection);
			MaterialInfo materialInfo = new MaterialInfo(alphaMulValue, alphaTestValue);      //todo need to see the og values.... set them over here, this is wrong for now

            if (indexAlpha != -1)
			{
				
				Print("Reset Alpha Values for " + chosenResource);
				tmp.SetParam("AlphaTest",alphaTestValue);
				tmp.SetParam("AlphaMul", alphaMulValue);
				
           	 	materialInfo.SetIndexAlphaMap(indexAlpha);

			}
			
            DecalInformation decalInformation = new DecalInformation(decalBaseInfo, decalPositionInfo, materialInfo);
			
			

			decalsSpawned.Insert(index, decalInformation);	
		}

	}
	
	
	void SpawnAnimatedFrames()
	{
		float distance = 2.0;

		foreach(int index, DecalInformation dInfo  : decalsSpawned)
		{
            DecalBaseInfo dBaseInfo = dInfo.decalBaseInfo;
            DecalPositionInfo dPositionInfo = dInfo.decalPositionInfo;
            MaterialInfo dMaterialInfo = dInfo.materialInfo;


			Decal d = dBaseInfo.decal;
			int currentFrame = dBaseInfo.currentFrame;
			array<ResourceName> tempFrames = materialsMap.Get(dBaseInfo.type);
			settings = MCF_SettingsManager.GetInstance().GetModSettings(ABL_MOD_ID);			//refresh!
			
			float maxAlphaMul = settings.Get("maxAlphaMul").ToFloat();
			float minAlphaTest = settings.Get("minAlphaTest").ToFloat();
			
			if (dMaterialInfo.alphaMul < maxAlphaMul)
			{
				if (d)
					m_world.RemoveDecal(d);
					
				TraceParam traceParam = dPositionInfo.traceParam;
				
				if (traceParam.TraceEnt) // spawn splatter below character
				{
					
					Material tmp;
					ResourceName chosenResource;
					chosenResource = tempFrames[dMaterialInfo.indexAlpha];
					tmp  = Material.GetOrLoadMaterial(chosenResource, 0);


					float modifiedAlphaMul;
					float modifiedAlphaTest;
					
					
					float minimumAlphaMulChange;
					float maximumAlphaMulChange;
					
					float minimumAlphaTestChange;
					float maximumAlphaTestChange;
					
					switch(dBaseInfo.type)
					{
						case EDecalType.BLOODPOOL:
						{
							minimumAlphaMulChange = settings.Get("bloodpoolMinimumAlphMulaChange").ToFloat();
							maximumAlphaMulChange = settings.Get("bloodpoolMaximumAlphaMulChange").ToFloat();
							
							minimumAlphaTestChange = 0;
							maximumAlphaTestChange = 0;
							
							
							
							break;
						}
						case EDecalType.WALLSPLATTER:
						{
							minimumAlphaMulChange = settings.Get("wallsplatterMinimumAlphaMulChange").ToFloat();
							maximumAlphaMulChange = settings.Get("wallsplatterMaximumAlphaMulChange").ToFloat();
							
							minimumAlphaTestChange = settings.Get("wallsplatterMinimumAlphaTestChange").ToFloat();
							maximumAlphaTestChange = settings.Get("wallsplatterMaximumAlphaTestChange").ToFloat();
							break;
						}
					
					}
					
					modifiedAlphaMul = dMaterialInfo.alphaMul + Math.RandomFloat(minimumAlphaMulChange, maximumAlphaMulChange);
					tmp.SetParam("AlphaMul", modifiedAlphaMul);

					
					if (dMaterialInfo.alphaTest > minAlphaTest)
					{
						modifiedAlphaTest = dMaterialInfo.alphaTest - Math.RandomFloat(minimumAlphaTestChange, maximumAlphaTestChange);
						tmp.SetParam("AlphaTest", modifiedAlphaTest);

					}
					else
						modifiedAlphaTest = dMaterialInfo.alphaTest;
					
					
					
					
					
					
					dMaterialInfo.alphaMul = modifiedAlphaMul; 
					dMaterialInfo.alphaTest = modifiedAlphaTest;
					
					Decal newDecal = m_world.CreateDecal(traceParam.TraceEnt, dPositionInfo.originPosition, dPositionInfo.projectionDirection, nearClip, farClip, dBaseInfo.rotation, dBaseInfo.size, 1, chosenResource, -1, materialColor);
					
					dBaseInfo.decal = newDecal;
					dBaseInfo.currentFrame = currentFrame;
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
	
	
	
	
	float SelectBloodpoolAngle(inout vector origin)
	{
		float tmpAngle;
		int randomNumber = Math.RandomIntInclusive(0,2);
		
		//todo not sure if this is needed anymore
		switch(randomNumber)
		{
			case 0:
			{
				tmpAngle = 0;
				break;
			}
			case 1:
			{
				tmpAngle = 90 * Math.DEG2RAD;
				origin[0] = origin[0] + 0.4;
				origin[2] = origin[2] - 0.4;
				break;
			}
			case 2:
			{
				tmpAngle = 180 * Math.DEG2RAD;
				origin[2] = origin[2] - 1;
				break;
			}
	
		}
		
		return tmpAngle;
	
	
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







class DecalInformation
{

    ref DecalBaseInfo decalBaseInfo;
    ref DecalPositionInfo decalPositionInfo;
	ref MaterialInfo materialInfo;
	


    void DecalInformation(DecalBaseInfo baseInfo, DecalPositionInfo positionInfo, MaterialInfo matInfo)
    {
        this.decalBaseInfo = baseInfo;
        this.decalPositionInfo = positionInfo;
        this.materialInfo = matInfo;

        
    }

}



class DecalBaseInfo
{
	Decal decal; 
	EDecalType type;


	int currentFrame;
	float size;
	float rotation;
	float currentAlphaMul;
	
    private bool isTerrainOnly;

    void DecalBaseInfo(Decal dec, EDecalType typ, int cf, int p_size, int p_rotation , int p_currentAlphaMul  )
    {
        this.decal = dec;
        this.type = typ;
        this.currentFrame = cf;
        this.size = p_size;
        this.rotation = p_rotation;
        this.currentAlphaMul = p_currentAlphaMul;
    }




    void SetIsTerrainOnly(bool val)
    {
        this.isTerrainOnly = val;
    }

    bool GetIsTerrainOnly()
    {
        return isTerrainOnly;
    }

}

class DecalPositionInfo
{
	ref TraceParam traceParam;
	vector hitPosition;
	vector hitDirection;
	vector originPosition;
	vector projectionDirection;


    void DecalPositionInfo(TraceParam tf, vector hitPos, vector hitDir, vector originPos, vector projDir)
    {
        this.traceParam = tf;
        this.hitPosition = hitPos;
        this.hitDirection = hitDir;
        this.originPosition = originPos;
        this.projectionDirection = projDir;

    }
	
}


class MaterialInfo
{
	float alphaMul;
	float alphaTest;

    int indexAlpha;     //to be used only with alpha blended maps not normal animated decals
	
	void MaterialInfo(float am, float at)
	{
		alphaMul = am;
		alphaTest = at;
	}


    void SetIndexAlphaMap(int id)
    {
        this.indexAlpha = id;
    }

    int GetIndexAlphaMap()
    {
        return indexAlpha;
    }
	

}





enum EDecalType
{
	BLOODPOOL,
	WALLSPLATTER,
	SINGLE_FRAME_GENERIC_SPLATTER
}