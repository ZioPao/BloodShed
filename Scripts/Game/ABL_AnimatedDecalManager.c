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

	//ref map<string, string> ablSettings;

	
	
	
	
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
	
		materialsMap.Insert(EDecalType.BLOODPOOL,{"{0376090EFF29D451}TestAlpha/001.emat","{5D9E204D40A45A5E}TestAlpha/002.emat","{A99667D54D79322A}TestAlpha/003.emat","{E04E72CA3FBF4640}TestAlpha/004.emat","{1446355232622E34}TestAlpha/005.emat","{4AAE1C118DEFA03B}TestAlpha/006.emat","{BEA65B898032C84F}TestAlpha/007.emat","{D91E362F686348EF}TestAlpha/008.emat","{2D1671B765BE209B}TestAlpha/009.emat","{30B2DE0B07A2FF29}TestAlpha/010.emat","{C4BA99930A7F975D}TestAlpha/011.emat","{9A52B0D0B5F21952}TestAlpha/012.emat","{6E5AF748B82F7126}TestAlpha/013.emat","{2782E257CAE9054C}TestAlpha/014.emat","{D38AA5CFC7346D38}TestAlpha/015.emat","{8D628C8C78B9E337}TestAlpha/016.emat","{796ACB1475648B43}TestAlpha/017.emat","{1ED2A6B29D350BE3}TestAlpha/018.emat","{EADAE12A90E86397}TestAlpha/019.emat","{3A178E46B1B20CAE}TestAlpha/020.emat","{CE1FC9DEBC6F64DA}TestAlpha/021.emat","{90F7E09D03E2EAD5}TestAlpha/022.emat","{64FFA7050E3F82A1}TestAlpha/023.emat","{2D27B21A7CF9F6CB}TestAlpha/024.emat","{D92FF58271249EBF}TestAlpha/025.emat","{87C7DCC1CEA910B0}TestAlpha/026.emat","{73CF9B59C37478C4}TestAlpha/027.emat","{1477F6FF2B25F864}TestAlpha/028.emat","{E07FB16726F89010}TestAlpha/029.emat","{FDDB1EDB44E44FA2}TestAlpha/030.emat","{09D35943493927D6}TestAlpha/031.emat","{573B7000F6B4A9D9}TestAlpha/032.emat","{A3333798FB69C1AD}TestAlpha/033.emat","{EAEB228789AFB5C7}TestAlpha/034.emat","{1EE3651F8472DDB3}TestAlpha/035.emat","{400B4C5C3BFF53BC}TestAlpha/036.emat","{B4030BC436223BC8}TestAlpha/037.emat","{D3BB6662DE73BB68}TestAlpha/038.emat","{27B321FAD3AED31C}TestAlpha/039.emat","{2F5D2EDDDD93EBA0}TestAlpha/040.emat","{DB556945D04E83D4}TestAlpha/041.emat","{85BD40066FC30DDB}TestAlpha/042.emat","{71B5079E621E65AF}TestAlpha/043.emat","{386D128110D811C5}TestAlpha/044.emat","{CC6555191D0579B1}TestAlpha/045.emat","{928D7C5AA288F7BE}TestAlpha/046.emat","{66853BC2AF559FCA}TestAlpha/047.emat","{013D566447041F6A}TestAlpha/048.emat","{F53511FC4AD9771E}TestAlpha/049.emat","{E891BE4028C5A8AC}TestAlpha/050.emat","{1C99F9D82518C0D8}TestAlpha/051.emat","{4271D09B9A954ED7}TestAlpha/052.emat","{B6799703974826A3}TestAlpha/053.emat","{FFA1821CE58E52C9}TestAlpha/054.emat","{0BA9C584E8533ABD}TestAlpha/055.emat","{5541ECC757DEB4B2}TestAlpha/056.emat","{A149AB5F5A03DCC6}TestAlpha/057.emat","{C6F1C6F9B2525C66}TestAlpha/058.emat","{32F98161BF8F3412}TestAlpha/059.emat","{E234EE0D9ED55B2B}TestAlpha/060.emat","{163CA9959308335F}TestAlpha/061.emat","{48D480D62C85BD50}TestAlpha/062.emat","{BCDCC74E2158D524}TestAlpha/063.emat","{F504D251539EA14E}TestAlpha/064.emat","{010C95C95E43C93A}TestAlpha/065.emat","{5FE4BC8AE1CE4735}TestAlpha/066.emat","{ABECFB12EC132F41}TestAlpha/067.emat","{CC5496B40442AFE1}TestAlpha/068.emat","{385CD12C099FC795}TestAlpha/069.emat","{25F87E906B831827}TestAlpha/070.emat","{D1F03908665E7053}TestAlpha/071.emat","{8F18104BD9D3FE5C}TestAlpha/072.emat","{7B1057D3D40E9628}TestAlpha/073.emat","{32C842CCA6C8E242}TestAlpha/074.emat","{C6C00554AB158A36}TestAlpha/075.emat","{98282C1714980439}TestAlpha/076.emat","{6C206B8F19456C4D}TestAlpha/077.emat","{0B980629F114ECED}TestAlpha/078.emat","{FF9041B1FCC98499}TestAlpha/079.emat","{05C86FEB05D025BC}TestAlpha/080.emat","{F1C02873080D4DC8}TestAlpha/081.emat","{AF280130B780C3C7}TestAlpha/082.emat","{5B2046A8BA5DABB3}TestAlpha/083.emat","{12F853B7C89BDFD9}TestAlpha/084.emat","{E6F0142FC546B7AD}TestAlpha/085.emat","{B8183D6C7ACB39A2}TestAlpha/086.emat","{4C107AF4771651D6}TestAlpha/087.emat","{2BA817529F47D176}TestAlpha/088.emat","{DFA050CA929AB902}TestAlpha/089.emat","{C204FF76F08666B0}TestAlpha/090.emat","{360CB8EEFD5B0EC4}TestAlpha/091.emat","{68E491AD42D680CB}TestAlpha/092.emat","{9CECD6354F0BE8BF}TestAlpha/093.emat","{D534C32A3DCD9CD5}TestAlpha/094.emat","{213C84B23010F4A1}TestAlpha/095.emat","{7FD4ADF18F9D7AAE}TestAlpha/096.emat","{8BDCEA69824012DA}TestAlpha/097.emat","{EC6487CF6A11927A}TestAlpha/098.emat","{186CC05767CCFA0E}TestAlpha/099.emat","{993370CFC79552AD}TestAlpha/100.emat","{6D3B3757CA483AD9}TestAlpha/101.emat","{33D31E1475C5B4D6}TestAlpha/102.emat","{C7DB598C7818DCA2}TestAlpha/103.emat","{8E034C930ADEA8C8}TestAlpha/104.emat","{7A0B0B0B0703C0BC}TestAlpha/105.emat","{24E32248B88E4EB3}TestAlpha/106.emat","{D0EB65D0B55326C7}TestAlpha/107.emat","{B75308765D02A667}TestAlpha/108.emat","{435B4FEE50DFCE13}TestAlpha/109.emat","{5EFFE05232C311A1}TestAlpha/110.emat","{AAF7A7CA3F1E79D5}TestAlpha/111.emat","{F41F8E898093F7DA}TestAlpha/112.emat","{0017C9118D4E9FAE}TestAlpha/113.emat","{49CFDC0EFF88EBC4}TestAlpha/114.emat","{BDC79B96F25583B0}TestAlpha/115.emat","{E32FB2D54DD80DBF}TestAlpha/116.emat","{1727F54D400565CB}TestAlpha/117.emat","{709F98EBA854E56B}TestAlpha/118.emat","{8497DF73A5898D1F}TestAlpha/119.emat","{545AB01F84D3E226}TestAlpha/120.emat","{A052F787890E8A52}TestAlpha/121.emat","{FEBADEC43683045D}TestAlpha/122.emat","{0AB2995C3B5E6C29}TestAlpha/123.emat","{436A8C4349981843}TestAlpha/124.emat","{B762CBDB44457037}TestAlpha/125.emat","{E98AE298FBC8FE38}TestAlpha/126.emat","{1D82A500F615964C}TestAlpha/127.emat","{7A3AC8A61E4416EC}TestAlpha/128.emat","{8E328F3E13997E98}TestAlpha/129.emat","{939620827185A12A}TestAlpha/130.emat","{679E671A7C58C95E}TestAlpha/131.emat","{39764E59C3D54751}TestAlpha/132.emat","{CD7E09C1CE082F25}TestAlpha/133.emat","{84A61CDEBCCE5B4F}TestAlpha/134.emat","{70AE5B46B113333B}TestAlpha/135.emat","{2E4672050E9EBD34}TestAlpha/136.emat","{DA4E359D0343D540}TestAlpha/137.emat","{BDF6583BEB1255E0}TestAlpha/138.emat","{49FE1FA3E6CF3D94}TestAlpha/139.emat","{41101084E8F20528}TestAlpha/140.emat","{B518571CE52F6D5C}TestAlpha/141.emat","{EBF07E5F5AA2E353}TestAlpha/142.emat","{1FF839C7577F8B27}TestAlpha/143.emat","{56202CD825B9FF4D}TestAlpha/144.emat","{A2286B4028649739}TestAlpha/145.emat","{FCC0420397E91936}TestAlpha/146.emat","{08C8059B9A347142}TestAlpha/147.emat","{6F70683D7265F1E2}TestAlpha/148.emat","{9B782FA57FB89996}TestAlpha/149.emat","{86DC80191DA44624}TestAlpha/150.emat","{72D4C78110792E50}TestAlpha/151.emat","{2C3CEEC2AFF4A05F}TestAlpha/152.emat","{D834A95AA229C82B}TestAlpha/153.emat","{91ECBC45D0EFBC41}TestAlpha/154.emat","{65E4FBDDDD32D435}TestAlpha/155.emat","{3B0CD29E62BF5A3A}TestAlpha/156.emat","{CF0495066F62324E}TestAlpha/157.emat","{A8BCF8A08733B2EE}TestAlpha/158.emat","{5CB4BF388AEEDA9A}TestAlpha/159.emat","{8C79D054ABB4B5A3}TestAlpha/160.emat","{787197CCA669DDD7}TestAlpha/161.emat","{2699BE8F19E453D8}TestAlpha/162.emat","{D291F91714393BAC}TestAlpha/163.emat","{9B49EC0866FF4FC6}TestAlpha/164.emat","{6F41AB906B2227B2}TestAlpha/165.emat","{31A982D3D4AFA9BD}TestAlpha/166.emat","{C5A1C54BD972C1C9}TestAlpha/167.emat","{A219A8ED31234169}TestAlpha/168.emat","{5611EF753CFE291D}TestAlpha/169.emat","{4BB540C95EE2F6AF}TestAlpha/170.emat","{BFBD0751533F9EDB}TestAlpha/171.emat","{E1552E12ECB210D4}TestAlpha/172.emat","{155D698AE16F78A0}TestAlpha/173.emat","{5C857C9593A90CCA}TestAlpha/174.emat","{A88D3B0D9E7464BE}TestAlpha/175.emat","{F665124E21F9EAB1}TestAlpha/176.emat","{026D55D62C2482C5}TestAlpha/177.emat","{65D53870C4750265}TestAlpha/178.emat","{91DD7FE8C9A86A11}TestAlpha/179.emat","{6B8551B230B1CB34}TestAlpha/180.emat","{9F8D162A3D6CA340}TestAlpha/181.emat","{C1653F6982E12D4F}TestAlpha/182.emat","{356D78F18F3C453B}TestAlpha/183.emat","{7CB56DEEFDFA3151}TestAlpha/184.emat","{88BD2A76F0275925}TestAlpha/185.emat","{D65503354FAAD72A}TestAlpha/186.emat","{225D44AD4277BF5E}TestAlpha/187.emat","{45E5290BAA263FFE}TestAlpha/188.emat","{B1ED6E93A7FB578A}TestAlpha/189.emat","{AC49C12FC5E78838}TestAlpha/190.emat","{584186B7C83AE04C}TestAlpha/191.emat","{06A9AFF477B76E43}TestAlpha/192.emat","{F2A1E86C7A6A0637}TestAlpha/193.emat","{BB79FD7308AC725D}TestAlpha/194.emat","{4F71BAEB05711A29}TestAlpha/195.emat","{119993A8BAFC9426}TestAlpha/196.emat","{E591D430B721FC52}TestAlpha/197.emat","{8229B9965F707CF2}TestAlpha/198.emat","{7621FE0E52AD1486}TestAlpha/199.emat"});
		materialsMap.Insert(EDecalType.WALLSPLATTER, {"{85A421FD8938D6B2}materials/wall_splatter_2/0.emat","{71AC666584E5BEC6}materials/wall_splatter_2/1.emat","{2F444F263B6830C9}materials/wall_splatter_2/2.emat","{DB4C08BE36B558BD}materials/wall_splatter_2/3.emat","{92941DA144732CD7}materials/wall_splatter_2/4.emat","{669C5A3949AE44A3}materials/wall_splatter_2/5.emat","{3874737AF623CAAC}materials/wall_splatter_2/6.emat","{CC7C34E2FBFEA2D8}materials/wall_splatter_2/7.emat","{ABC4594413AF2278}materials/wall_splatter_2/8.emat","{5FCC1EDC1E724A0C}materials/wall_splatter_2/9.emat","{5B2DD19AD7874B53}materials/wall_splatter_2/10.emat","{AF259602DA5A2327}materials/wall_splatter_2/11.emat","{F1CDBF4165D7AD28}materials/wall_splatter_2/12.emat","{05C5F8D9680AC55C}materials/wall_splatter_2/13.emat","{4C1DEDC61ACCB136}materials/wall_splatter_2/14.emat","{B815AA5E1711D942}materials/wall_splatter_2/15.emat","{E6FD831DA89C574D}materials/wall_splatter_2/16.emat","{12F5C485A5413F39}materials/wall_splatter_2/17.emat","{754DA9234D10BF99}materials/wall_splatter_2/18.emat","{8145EEBB40CDD7ED}materials/wall_splatter_2/19.emat","{518881D76197B8D4}materials/wall_splatter_2/20.emat","{A580C64F6C4AD0A0}materials/wall_splatter_2/21.emat","{FB68EF0CD3C75EAF}materials/wall_splatter_2/22.emat","{0F60A894DE1A36DB}materials/wall_splatter_2/23.emat","{46B8BD8BACDC42B1}materials/wall_splatter_2/24.emat","{B2B0FA13A1012AC5}materials/wall_splatter_2/25.emat","{EC58D3501E8CA4CA}materials/wall_splatter_2/26.emat","{185094C81351CCBE}materials/wall_splatter_2/27.emat","{7FE8F96EFB004C1E}materials/wall_splatter_2/28.emat","{8BE0BEF6F6DD246A}materials/wall_splatter_2/29.emat","{9644114A94C1FBD8}materials/wall_splatter_2/30.emat","{624C56D2991C93AC}materials/wall_splatter_2/31.emat","{3CA47F9126911DA3}materials/wall_splatter_2/32.emat","{C8AC38092B4C75D7}materials/wall_splatter_2/33.emat","{81742D16598A01BD}materials/wall_splatter_2/34.emat","{757C6A8E545769C9}materials/wall_splatter_2/35.emat","{2B9443CDEBDAE7C6}materials/wall_splatter_2/36.emat","{DF9C0455E6078FB2}materials/wall_splatter_2/37.emat","{B82469F30E560F12}materials/wall_splatter_2/38.emat","{4C2C2E6B038B6766}materials/wall_splatter_2/39.emat","{44C2214C0DB65FDA}materials/wall_splatter_2/40.emat","{B0CA66D4006B37AE}materials/wall_splatter_2/41.emat","{EE224F97BFE6B9A1}materials/wall_splatter_2/42.emat","{1A2A080FB23BD1D5}materials/wall_splatter_2/43.emat","{53F21D10C0FDA5BF}materials/wall_splatter_2/44.emat","{A7FA5A88CD20CDCB}materials/wall_splatter_2/45.emat","{F91273CB72AD43C4}materials/wall_splatter_2/46.emat","{0D1A34537F702BB0}materials/wall_splatter_2/47.emat","{6AA259F59721AB10}materials/wall_splatter_2/48.emat","{9EAA1E6D9AFCC364}materials/wall_splatter_2/49.emat","{830EB1D1F8E01CD6}materials/wall_splatter_2/50.emat","{7706F649F53D74A2}materials/wall_splatter_2/51.emat","{29EEDF0A4AB0FAAD}materials/wall_splatter_2/52.emat","{DDE69892476D92D9}materials/wall_splatter_2/53.emat","{943E8D8D35ABE6B3}materials/wall_splatter_2/54.emat","{6036CA1538768EC7}materials/wall_splatter_2/55.emat","{3EDEE35687FB00C8}materials/wall_splatter_2/56.emat","{CAD6A4CE8A2668BC}materials/wall_splatter_2/57.emat","{AD6EC9686277E81C}materials/wall_splatter_2/58.emat","{59668EF06FAA8068}materials/wall_splatter_2/59.emat","{89ABE19C4EF0EF51}materials/wall_splatter_2/60.emat","{7DA3A604432D8725}materials/wall_splatter_2/61.emat","{234B8F47FCA0092A}materials/wall_splatter_2/62.emat","{D743C8DFF17D615E}materials/wall_splatter_2/63.emat","{9E9BDDC083BB1534}materials/wall_splatter_2/64.emat","{6A939A588E667D40}materials/wall_splatter_2/65.emat","{347BB31B31EBF34F}materials/wall_splatter_2/66.emat","{C073F4833C369B3B}materials/wall_splatter_2/67.emat","{A7CB9925D4671B9B}materials/wall_splatter_2/68.emat","{53C3DEBDD9BA73EF}materials/wall_splatter_2/69.emat","{4E677101BBA6AC5D}materials/wall_splatter_2/70.emat","{BA6F3699B67BC429}materials/wall_splatter_2/71.emat","{E4871FDA09F64A26}materials/wall_splatter_2/72.emat","{108F5842042B2252}materials/wall_splatter_2/73.emat","{59574D5D76ED5638}materials/wall_splatter_2/74.emat","{AD5F0AC57B303E4C}materials/wall_splatter_2/75.emat","{F3B72386C4BDB043}materials/wall_splatter_2/76.emat","{07BF641EC960D837}materials/wall_splatter_2/77.emat","{600709B821315897}materials/wall_splatter_2/78.emat","{940F4E202CEC30E3}materials/wall_splatter_2/79.emat","{6E57607AD5F591C6}materials/wall_splatter_2/80.emat","{9A5F27E2D828F9B2}materials/wall_splatter_2/81.emat","{C4B70EA167A577BD}materials/wall_splatter_2/82.emat","{30BF49396A781FC9}materials/wall_splatter_2/83.emat","{79675C2618BE6BA3}materials/wall_splatter_2/84.emat","{8D6F1BBE156303D7}materials/wall_splatter_2/85.emat","{D38732FDAAEE8DD8}materials/wall_splatter_2/86.emat","{278F7565A733E5AC}materials/wall_splatter_2/87.emat","{403718C34F62650C}materials/wall_splatter_2/88.emat","{B43F5F5B42BF0D78}materials/wall_splatter_2/89.emat","{A99BF0E720A3D2CA}materials/wall_splatter_2/90.emat","{5D93B77F2D7EBABE}materials/wall_splatter_2/91.emat","{037B9E3C92F334B1}materials/wall_splatter_2/92.emat","{F773D9A49F2E5CC5}materials/wall_splatter_2/93.emat","{BEABCCBBEDE828AF}materials/wall_splatter_2/94.emat","{4AA38B23E03540DB}materials/wall_splatter_2/95.emat","{144BA2605FB8CED4}materials/wall_splatter_2/96.emat","{E043E5F85265A6A0}materials/wall_splatter_2/97.emat","{87FB885EBA342600}materials/wall_splatter_2/98.emat","{73F3CFC6B7E94E74}materials/wall_splatter_2/99.emat"});
		materialsMap.Insert(EDecalType.SINGLE_FRAME_GENERIC_SPLATTER, {"{B3196D0D8CB491D5}materials/ground_splatter/001.emat"});
		
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
			MaterialInfo materialInfo = new MaterialInfo(alphaMulValue, 0);      //todo need to see the og values.... set them over here, this is wrong for now

            if (indexAlpha != -1)
			{
				
				Print("Reset Alpha Values for " + chosenResource);
				//tmp.SetParam("AlphaTest",alphaTestValue);
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
			
			float maxAlphaTest = settings.Get("maxAlphaTest").ToFloat();

			
			if (dMaterialInfo.alphaMul < maxAlphaTest)
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
					float alphaTest;
					float minimumAlphaChange;
					float maximumAlphaChange;
					
					switch(dBaseInfo.type)
					{
						case EDecalType.BLOODPOOL:
						{
							minimumAlphaChange = settings.Get("bloodpoolMinimumAlphaChange").ToFloat();
							maximumAlphaChange = settings.Get("bloodpoolMaximumAlphaChange").ToFloat();
							break;
						}
						case EDecalType.WALLSPLATTER:
						{
							minimumAlphaChange = settings.Get("wallsplatterMinimumAlphaChange").ToFloat();
							maximumAlphaChange = settings.Get("wallsplatterMaximumAlphaChange").ToFloat();
							break;
						}
					
					}
					
					modifiedAlphaMul = dMaterialInfo.alphaMul + Math.RandomFloat(minimumAlphaChange, maximumAlphaChange);
					tmp.SetParam("AlphaMul", modifiedAlphaMul);

					
					dMaterialInfo.alphaMul = modifiedAlphaMul; 



					
					
					Decal newDecal = m_world.CreateDecal(traceParam.TraceEnt, dPositionInfo.originPosition, dPositionInfo.projectionDirection, nearClip, farClip, dBaseInfo.rotation, dBaseInfo.size, 1, chosenResource, -1, materialColor);
					
					//currentFrame++;
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