class BS_AnimatedBloodManagerClass : GenericEntityClass
{
}

class BS_AnimatedBloodManager : GenericEntity
{

	static ref map<EDecalType, ref array<ResourceName>> materialsMap;
	ref map<int, ref DecalInformation> decalsSpawned;
	ref map<ref EntityID, ref BloodTrailInfo> bloodTrailsInfoMap;

	ref array<IEntity> bleedingCharacters;

	ref static array<DecalWrapper> currentPlayerDecals;
	ref array<DecalWrapper> currentCharacterDecals;

	// won't work. we'd need to save the time and hten compare it to the current one that's gonna be spawned

	const string ABL_MOD_ID = "59D925199B6E6BFD"; // it's probably possible to get this in a better way but ok
	const ResourceName weaponSplatterMaterial = "{098960A4823D679F}Materials/WeaponSplatters/001.emat";
	ref map<string, string> settings;

	int materialColor; // todo make this dynamic
	float waitTimeBetweenFrames;
	float currentTime;

	static BS_AnimatedBloodManager instance;

	ref array<Material> materialsLoaded;
	// ref array<Material> wallsplattersLoaded;
	// ref array<Material> genericSplattersLoaded;

	// would be better if it's all a static class? No we can't allocate stuff maybe? I dont remember
	static BS_AnimatedBloodManager GetInstance()
	{
		return instance;
	}

	void BS_AnimatedBloodManager(IEntitySource src, IEntity parent)
	{

		SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
		SetFlags(EntityFlags.ACTIVE, true);

		Math.Randomize(-1); // todo this is not really random.

		// Print("ADM: Starting up ADM");
		decalsSpawned = new map<int, ref DecalInformation>();
		materialsMap = new map<EDecalType, ref array<ResourceName>>();

		materialsMap.Insert(EDecalType.BLOODPOOL, {"{835E7FE497FE789E}Materials/BloodSplatters/001.emat", "{DDB656A72873F691}Materials/BloodSplatters/002.emat", "{29BE113F25AE9EE5}Materials/BloodSplatters/003.emat", "{606604205768EA8F}Materials/BloodSplatters/004.emat",
												   "{946E43B85AB582FB}Materials/BloodSplatters/005.emat", "{CA866AFBE5380CF4}Materials/BloodSplatters/006.emat", "{3E8E2D63E8E56480}Materials/BloodSplatters/007.emat", "{593640C500B4E420}Materials/BloodSplatters/008.emat", "{AD3E075D0D698C54}Materials/BloodSplatters/009.emat",
												   "{B09AA8E16F7553E6}Materials/BloodSplatters/010.emat", "{4492EF7962A83B92}Materials/BloodSplatters/011.emat", "{1A7AC63ADD25B59D}Materials/BloodSplatters/012.emat", "{EE7281A2D0F8DDE9}Materials/BloodSplatters/013.emat", "{A7AA94BDA23EA983}Materials/BloodSplatters/014.emat",
												   "{53A2D325AFE3C1F7}Materials/BloodSplatters/015.emat", "{0D4AFA66106E4FF8}Materials/BloodSplatters/016.emat", "{F942BDFE1DB3278C}Materials/BloodSplatters/017.emat", "{9EFAD058F5E2A72C}Materials/BloodSplatters/018.emat", "{6AF297C0F83FCF58}Materials/BloodSplatters/019.emat",
												   "{BA3FF8ACD965A061}Materials/BloodSplatters/020.emat", "{4E37BF34D4B8C815}Materials/BloodSplatters/021.emat", "{10DF96776B35461A}Materials/BloodSplatters/022.emat", "{E4D7D1EF66E82E6E}Materials/BloodSplatters/023.emat", "{AD0FC4F0142E5A04}Materials/BloodSplatters/024.emat",
												   "{5907836819F33270}Materials/BloodSplatters/025.emat", "{07EFAA2BA67EBC7F}Materials/BloodSplatters/026.emat", "{F3E7EDB3ABA3D40B}Materials/BloodSplatters/027.emat", "{945F801543F254AB}Materials/BloodSplatters/028.emat", "{6057C78D4E2F3CDF}Materials/BloodSplatters/029.emat",
												   "{7DF368312C33E36D}Materials/BloodSplatters/030.emat", "{89FB2FA921EE8B19}Materials/BloodSplatters/031.emat", "{D71306EA9E630516}Materials/BloodSplatters/032.emat", "{231B417293BE6D62}Materials/BloodSplatters/033.emat", "{6AC3546DE1781908}Materials/BloodSplatters/034.emat",
												   "{9ECB13F5ECA5717C}Materials/BloodSplatters/035.emat", "{C0233AB65328FF73}Materials/BloodSplatters/036.emat", "{342B7D2E5EF59707}Materials/BloodSplatters/037.emat", "{53931088B6A417A7}Materials/BloodSplatters/038.emat", "{A79B5710BB797FD3}Materials/BloodSplatters/039.emat",
												   "{AF755837B544476F}Materials/BloodSplatters/040.emat", "{5B7D1FAFB8992F1B}Materials/BloodSplatters/041.emat", "{059536EC0714A114}Materials/BloodSplatters/042.emat", "{F19D71740AC9C960}Materials/BloodSplatters/043.emat", "{B845646B780FBD0A}Materials/BloodSplatters/044.emat",
												   "{4C4D23F375D2D57E}Materials/BloodSplatters/045.emat", "{12A50AB0CA5F5B71}Materials/BloodSplatters/046.emat", "{E6AD4D28C7823305}Materials/BloodSplatters/047.emat", "{8115208E2FD3B3A5}Materials/BloodSplatters/048.emat", "{751D6716220EDBD1}Materials/BloodSplatters/049.emat",
												   "{68B9C8AA40120463}Materials/BloodSplatters/050.emat", "{9CB18F324DCF6C17}Materials/BloodSplatters/051.emat", "{C259A671F242E218}Materials/BloodSplatters/052.emat", "{3651E1E9FF9F8A6C}Materials/BloodSplatters/053.emat", "{7F89F4F68D59FE06}Materials/BloodSplatters/054.emat",
												   "{8B81B36E80849672}Materials/BloodSplatters/055.emat", "{D5699A2D3F09187D}Materials/BloodSplatters/056.emat", "{2161DDB532D47009}Materials/BloodSplatters/057.emat", "{46D9B013DA85F0A9}Materials/BloodSplatters/058.emat", "{B2D1F78BD75898DD}Materials/BloodSplatters/059.emat",
												   "{621C98E7F602F7E4}Materials/BloodSplatters/060.emat", "{9614DF7FFBDF9F90}Materials/BloodSplatters/061.emat", "{C8FCF63C4452119F}Materials/BloodSplatters/062.emat", "{3CF4B1A4498F79EB}Materials/BloodSplatters/063.emat", "{752CA4BB3B490D81}Materials/BloodSplatters/064.emat",
												   "{8124E323369465F5}Materials/BloodSplatters/065.emat", "{DFCCCA608919EBFA}Materials/BloodSplatters/066.emat", "{2BC48DF884C4838E}Materials/BloodSplatters/067.emat", "{4C7CE05E6C95032E}Materials/BloodSplatters/068.emat", "{B874A7C661486B5A}Materials/BloodSplatters/069.emat",
												   "{A5D0087A0354B4E8}Materials/BloodSplatters/070.emat", "{51D84FE20E89DC9C}Materials/BloodSplatters/071.emat", "{0F3066A1B1045293}Materials/BloodSplatters/072.emat", "{FB382139BCD93AE7}Materials/BloodSplatters/073.emat", "{B2E03426CE1F4E8D}Materials/BloodSplatters/074.emat",
												   "{46E873BEC3C226F9}Materials/BloodSplatters/075.emat", "{18005AFD7C4FA8F6}Materials/BloodSplatters/076.emat", "{EC081D657192C082}Materials/BloodSplatters/077.emat", "{8BB070C399C34022}Materials/BloodSplatters/078.emat", "{7FB8375B941E2856}Materials/BloodSplatters/079.emat",
												   "{85E019016D078973}Materials/BloodSplatters/080.emat", "{71E85E9960DAE107}Materials/BloodSplatters/081.emat", "{2F0077DADF576F08}Materials/BloodSplatters/082.emat", "{DB083042D28A077C}Materials/BloodSplatters/083.emat", "{92D0255DA04C7316}Materials/BloodSplatters/084.emat",
												   "{66D862C5AD911B62}Materials/BloodSplatters/085.emat", "{38304B86121C956D}Materials/BloodSplatters/086.emat", "{CC380C1E1FC1FD19}Materials/BloodSplatters/087.emat", "{AB8061B8F7907DB9}Materials/BloodSplatters/088.emat", "{5F882620FA4D15CD}Materials/BloodSplatters/089.emat",
												   "{422C899C9851CA7F}Materials/BloodSplatters/090.emat", "{B624CE04958CA20B}Materials/BloodSplatters/091.emat", "{E8CCE7472A012C04}Materials/BloodSplatters/092.emat", "{1CC4A0DF27DC4470}Materials/BloodSplatters/093.emat", "{551CB5C0551A301A}Materials/BloodSplatters/094.emat",
												   "{A114F25858C7586E}Materials/BloodSplatters/095.emat", "{FFFCDB1BE74AD661}Materials/BloodSplatters/096.emat", "{0BF49C83EA97BE15}Materials/BloodSplatters/097.emat", "{6C4CF12502C63EB5}Materials/BloodSplatters/098.emat", "{9844B6BD0F1B56C1}Materials/BloodSplatters/099.emat",
												   "{191B0625AF42FE62}Materials/BloodSplatters/100.emat"});

		materialsMap.Insert(EDecalType.WALLSPLATTER, {"{22872EB748EA13CF}Materials/WallSplatters/001.emat", "{7C6F07F4F7679DC0}Materials/WallSplatters/002.emat", "{8867406CFABAF5B4}Materials/WallSplatters/003.emat", "{C1BF5573887C81DE}Materials/WallSplatters/004.emat",
													  "{35B712EB85A1E9AA}Materials/WallSplatters/005.emat", "{6B5F3BA83A2C67A5}Materials/WallSplatters/006.emat", "{9F577C3037F10FD1}Materials/WallSplatters/007.emat", "{F8EF1196DFA08F71}Materials/WallSplatters/008.emat", "{0CE7560ED27DE705}Materials/WallSplatters/009.emat",
													  "{1143F9B2B06138B7}Materials/WallSplatters/010.emat", "{E54BBE2ABDBC50C3}Materials/WallSplatters/011.emat", "{BBA397690231DECC}Materials/WallSplatters/012.emat", "{4FABD0F10FECB6B8}Materials/WallSplatters/013.emat", "{0673C5EE7D2AC2D2}Materials/WallSplatters/014.emat",
													  "{F27B827670F7AAA6}Materials/WallSplatters/015.emat", "{AC93AB35CF7A24A9}Materials/WallSplatters/016.emat", "{589BECADC2A74CDD}Materials/WallSplatters/017.emat", "{3F23810B2AF6CC7D}Materials/WallSplatters/018.emat", "{CB2BC693272BA409}Materials/WallSplatters/019.emat",
													  "{1BE6A9FF0671CB30}Materials/WallSplatters/020.emat", "{EFEEEE670BACA344}Materials/WallSplatters/021.emat", "{B106C724B4212D4B}Materials/WallSplatters/022.emat", "{450E80BCB9FC453F}Materials/WallSplatters/023.emat", "{0CD695A3CB3A3155}Materials/WallSplatters/024.emat",
													  "{F8DED23BC6E75921}Materials/WallSplatters/025.emat", "{A636FB78796AD72E}Materials/WallSplatters/026.emat", "{523EBCE074B7BF5A}Materials/WallSplatters/027.emat", "{3586D1469CE63FFA}Materials/WallSplatters/028.emat", "{C18E96DE913B578E}Materials/WallSplatters/029.emat",
													  "{DC2A3962F327883C}Materials/WallSplatters/030.emat", "{28227EFAFEFAE048}Materials/WallSplatters/031.emat", "{76CA57B941776E47}Materials/WallSplatters/032.emat", "{82C210214CAA0633}Materials/WallSplatters/033.emat", "{CB1A053E3E6C7259}Materials/WallSplatters/034.emat",
													  "{3F1242A633B11A2D}Materials/WallSplatters/035.emat", "{61FA6BE58C3C9422}Materials/WallSplatters/036.emat", "{95F22C7D81E1FC56}Materials/WallSplatters/037.emat", "{F24A41DB69B07CF6}Materials/WallSplatters/038.emat", "{06420643646D1482}Materials/WallSplatters/039.emat",
													  "{0EAC09646A502C3E}Materials/WallSplatters/040.emat", "{FAA44EFC678D444A}Materials/WallSplatters/041.emat", "{A44C67BFD800CA45}Materials/WallSplatters/042.emat", "{50442027D5DDA231}Materials/WallSplatters/043.emat", "{199C3538A71BD65B}Materials/WallSplatters/044.emat",
													  "{ED9472A0AAC6BE2F}Materials/WallSplatters/045.emat", "{B37C5BE3154B3020}Materials/WallSplatters/046.emat", "{47741C7B18965854}Materials/WallSplatters/047.emat", "{20CC71DDF0C7D8F4}Materials/WallSplatters/048.emat", "{D4C43645FD1AB080}Materials/WallSplatters/049.emat",
													  "{C96099F99F066F32}Materials/WallSplatters/050.emat", "{3D68DE6192DB0746}Materials/WallSplatters/051.emat", "{6380F7222D568949}Materials/WallSplatters/052.emat", "{9788B0BA208BE13D}Materials/WallSplatters/053.emat", "{DE50A5A5524D9557}Materials/WallSplatters/054.emat",
													  "{2A58E23D5F90FD23}Materials/WallSplatters/055.emat", "{74B0CB7EE01D732C}Materials/WallSplatters/056.emat", "{80B88CE6EDC01B58}Materials/WallSplatters/057.emat", "{E700E14005919BF8}Materials/WallSplatters/058.emat", "{1308A6D8084CF38C}Materials/WallSplatters/059.emat",
													  "{C3C5C9B429169CB5}Materials/WallSplatters/060.emat", "{37CD8E2C24CBF4C1}Materials/WallSplatters/061.emat", "{6925A76F9B467ACE}Materials/WallSplatters/062.emat", "{9D2DE0F7969B12BA}Materials/WallSplatters/063.emat", "{D4F5F5E8E45D66D0}Materials/WallSplatters/064.emat",
													  "{20FDB270E9800EA4}Materials/WallSplatters/065.emat", "{7E159B33560D80AB}Materials/WallSplatters/066.emat", "{8A1DDCAB5BD0E8DF}Materials/WallSplatters/067.emat", "{EDA5B10DB381687F}Materials/WallSplatters/068.emat", "{19ADF695BE5C000B}Materials/WallSplatters/069.emat",
													  "{04095929DC40DFB9}Materials/WallSplatters/070.emat", "{F0011EB1D19DB7CD}Materials/WallSplatters/071.emat", "{AEE937F26E1039C2}Materials/WallSplatters/072.emat", "{5AE1706A63CD51B6}Materials/WallSplatters/073.emat", "{13396575110B25DC}Materials/WallSplatters/074.emat",
													  "{E73122ED1CD64DA8}Materials/WallSplatters/075.emat", "{B9D90BAEA35BC3A7}Materials/WallSplatters/076.emat", "{4DD14C36AE86ABD3}Materials/WallSplatters/077.emat", "{2A69219046D72B73}Materials/WallSplatters/078.emat", "{DE6166084B0A4307}Materials/WallSplatters/079.emat",
													  "{24394852B213E222}Materials/WallSplatters/080.emat", "{D0310FCABFCE8A56}Materials/WallSplatters/081.emat", "{8ED9268900430459}Materials/WallSplatters/082.emat", "{7AD161110D9E6C2D}Materials/WallSplatters/083.emat", "{3309740E7F581847}Materials/WallSplatters/084.emat",
													  "{C701339672857033}Materials/WallSplatters/085.emat", "{99E91AD5CD08FE3C}Materials/WallSplatters/086.emat", "{6DE15D4DC0D59648}Materials/WallSplatters/087.emat", "{0A5930EB288416E8}Materials/WallSplatters/088.emat", "{FE51777325597E9C}Materials/WallSplatters/089.emat",
													  "{E3F5D8CF4745A12E}Materials/WallSplatters/090.emat", "{17FD9F574A98C95A}Materials/WallSplatters/091.emat", "{4915B614F5154755}Materials/WallSplatters/092.emat", "{BD1DF18CF8C82F21}Materials/WallSplatters/093.emat", "{F4C5E4938A0E5B4B}Materials/WallSplatters/094.emat",
													  "{00CDA30B87D3333F}Materials/WallSplatters/095.emat", "{5E258A48385EBD30}Materials/WallSplatters/096.emat", "{AA2DCDD03583D544}Materials/WallSplatters/097.emat", "{CD95A076DDD255E4}Materials/WallSplatters/098.emat", "{399DE7EED00F3D90}Materials/WallSplatters/099.emat",
													  "{B8C2577670569533}Materials/WallSplatters/100.emat"});

		materialsMap.Insert(EDecalType.SINGLE_FRAME_GENERIC_SPLATTER, {"{926152FC7FC453C7}Materials/GenericSplatters/001.emat", "{CC897BBFC049DDC8}Materials/GenericSplatters/002.emat", "{38813C27CD94B5BC}Materials/GenericSplatters/003.emat",
																	   "{71592938BF52C1D6}Materials/GenericSplatters/004.emat", "{85516EA0B28FA9A2}Materials/GenericSplatters/005.emat"});

		// temp materials, not final
		materialsMap.Insert(EDecalType.DROPLETS, {
													 "{38813C27CD94B5BC}Materials/GenericSplatters/003.emat",
													 "{71592938BF52C1D6}Materials/GenericSplatters/004.emat",
													 "{85516EA0B28FA9A2}Materials/GenericSplatters/005.emat",
												 });

		// lets load everything right here?
		materialsLoaded = new array<Material>();

		Print("Loading Bloodpools");
		foreach (ResourceName rsBloodpool : materialsMap.Get(EDecalType.BLOODPOOL))
			materialsLoaded.Insert(Material.GetOrLoadMaterial(rsBloodpool, 0));

		Print("Loading wall splatters");
		foreach (ResourceName rsWallsplatter : materialsMap.Get(EDecalType.WALLSPLATTER))
			materialsLoaded.Insert(Material.GetOrLoadMaterial(rsWallsplatter, 0));

		Print("Loading Generic Splatters");
		foreach (ResourceName rsGenericSplatter : materialsMap.Get(EDecalType.SINGLE_FRAME_GENERIC_SPLATTER))
			materialsLoaded.Insert(Material.GetOrLoadMaterial(rsGenericSplatter, 0));

		// Print("Loading Droplets");
		// foreach (ResourceName rsDroplets : materialsMap.Get(EDecalType.DROPLETS))
		//	materialsLoaded.Insert(Material.GetOrLoadMaterial(rsDroplets, 0));
		instance = this;

		materialColor = Color.FromRGBA(128, 0, 0, 255).PackToInt();

		currentCharacterDecals = new array<DecalWrapper>();
		bleedingCharacters = new array<IEntity>();

		if (!currentPlayerDecals)
			currentPlayerDecals = new array<DecalWrapper>();

		// MCF_Debug.dbgShapes = new array<Shape>();

		SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
	}

	override void EOnInit(IEntity owner) //! EntityEvent.INIT
	{
		super.EOnInit(owner);
		// Allocate it whenever called. When called, let's start.
	}

	override void EOnFrame(IEntity owner, float timeSlice) //! EntityEvent.FRAME
	{

		if (decalsSpawned.Count() > 0)
		{
			currentTime += timeSlice;
			if (currentTime > waitTimeBetweenFrames)
			{
				AnimateDecals();

				currentTime = 0;
				// settings = MCF_SettingsManager.GetModSettings(ABL_MOD_ID);
				waitTimeBetweenFrames = 0.033;

				// settings.Get("waitTimeBetweenFrames").ToFloat();
			}
		}
	}

	void SpawnDecal(TraceParam traceParam, EDecalType type, vector origin, vector projection, float nearClip, float farClip, float angle, float size, float alphaTestValue = -1, float alphaMulValue = -1, int lifetime = -1)
	{

		// Print("Spawning decal: " + type);
		array<ResourceName> refResources = materialsMap.Get(type);
		int randomMaterialIndex = Math.RandomIntInclusive(0, refResources.Count() - 1);
		ResourceName materialResource = refResources[randomMaterialIndex];
		Material material = Material.GetMaterial(materialResource);
		Decal decal;

		if (traceParam.TraceEnt)
		{
			World tmpWorld = GetGame().GetWorld();
			decal = tmpWorld.CreateDecal(traceParam.TraceEnt, origin, projection, nearClip, farClip, angle, size, 1, materialResource, lifetime, materialColor);

			DecalBaseInfo decalBaseInfo = new DecalBaseInfo(decal, type, 0, size, angle, 1);
			DecalPositionInfo decalPositionInfo = new DecalPositionInfo(traceParam, origin, projection);
			MaterialInfo materialInfo = new MaterialInfo(alphaMulValue, alphaTestValue); // todo need to see the og values.... set them over here, this is wrong for now

			if (alphaTestValue > 0)
				material.SetParam("AlphaTest", alphaTestValue);

			if (alphaMulValue > 0)
				material.SetParam("AlphaMul", alphaMulValue);

			materialInfo.SetIndexAlphaMap(randomMaterialIndex);
			DecalInformation decalInformation = new DecalInformation(decalBaseInfo, decalPositionInfo, materialInfo);

			if (type != EDecalType.SINGLE_FRAME_GENERIC_SPLATTER && type != EDecalType.DROPLETS)
			{

				// try to insert it into the decalsSpawned map
				int index = Math.RandomInt(-10000, 10000);

				// todo really inefficient
				while (decalsSpawned.Get(index))
					index = Math.RandomInt(-10000, 10000);

				decalsSpawned.Insert(index, decalInformation);
			}
		}
	}

	void SpawnDroplets(IEntity character, vector hitPosition)
	{

		float distance = 2.0;
		float nearClip = 0;
		float farClip = 2.0;
		float angle;
		float size;

		vector intersectionPosition;
		vector origin;
		vector projection;

		TraceParam traceParam = GetSurfaceIntersection(character, GetGame().GetWorld(), hitPosition, Vector(0, -1, 0), distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
		origin = character.GetOrigin() + Vector(0, distance / 4, 0);
		projection = -traceParam.TraceNorm;

		// projection should be a bit randomized

		size = Math.RandomFloatInclusive(0.2, 0.4);
		angle = Math.RandomFloatInclusive(-360, 360);

		SpawnDecal(traceParam, EDecalType.DROPLETS, origin, projection, nearClip, farClip, angle, size);
	}

	void SpawnWallSplatter(IEntity character, vector hitPosition, vector hitDirection)
	{
		Print("Generating WallSplatter");

		// Basic variables
		int randomMaterialIndex;
		array<string> refResources;
		ResourceName material;

		float distance = 2.0;
		float nearClip = 0;
		float farClip = 2.0;
		float angle;
		float size;
		float alphaMulValue = 1.4;
		float alphaTestValue = 3; // starting point
		int color;

		TraceParam traceParam;
		vector origin;
		vector projection;
		vector intersectionPosition;
		vector correctedDirection;

		// Check intersection and setup vectors
		traceParam = GetSurfaceIntersection(character, GetGame().GetWorld(), hitPosition, hitDirection, distance, TraceFlags.ENTS, intersectionPosition);
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

		if (traceParam.TraceEnt)
		{
			// angle = Math.RandomFloatInclusive(-360, 360);
			size = Math.RandomFloatInclusive(0.2, 0.8);
			SpawnDecal(traceParam, EDecalType.WALLSPLATTER, origin, projection, nearClip, farClip, angle, size, alphaTestValue, alphaMulValue);
		}
	}

	/* Really similiar to wallsplatter but more generic*/
	void SpawnGenericSplatter(IEntity character, vector hitPosition, vector hitDirection)
	{
		// Basic variables
		int randomMaterialIndex;
		array<string> refResources;
		ResourceName material;

		float distance = 2.0;
		float nearClip = 0;
		float farClip = 2.0;
		float angle;
		float size;
		int color;

		TraceParam traceParam;
		vector origin;
		vector projection;
		vector intersectionPosition;
		vector correctedDirection;

		// Fix up some stuff
		correctedDirection = hitDirection;
		correctedDirection[1] = correctedDirection[1] - 1.5; // to prevent them from being upside down

		// Check intersection and setup vectors
		traceParam = GetSurfaceIntersection(character, GetGame().GetWorld(), hitPosition, correctedDirection, distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
		origin = hitPosition + Vector(0, distance / 4, 0);
		projection = vector.Lerp(-traceParam.TraceNorm, correctedDirection, 0.1);

		if (traceParam.TraceEnt)
		{
			// angle = Math.RandomFloatInclusive(-360, 360);
			size = Math.RandomFloatInclusive(0.2, 0.8);
			SpawnDecal(traceParam, EDecalType.SINGLE_FRAME_GENERIC_SPLATTER, origin, projection, nearClip, farClip, angle, size);
		}
	}

	void SpawnGroundBloodpool(IEntity character, vector hitPosition, vector hitDirection, int nodeId)
	{
		Print("Triggered SpawnGroundBloodpool");

		// Basic variables
		int randomMaterialIndex;
		array<string> refResources;
		ResourceName materialResourceName;
		Material material;

		float distance = 2.0;
		float nearClip = 0;
		float farClip = 2.0;
		float angle;
		float size;
		float alphaMulValue = 0.55;
		float alphaTestValue = 0.670; // shouldn't decrease.

		TraceParam traceParam;
		vector origin;
		vector projection;
		vector intersectionPosition;
		vector correctedDirection;

		vector characterBoneMatrix[4];
		vector correctedHitPosition;

		// Get a random blood pool and variables from settings
		// if (settings)
		//	size = settings.Get("bloodpoolSize").ToFloat();
		// else
		size = 1.5;

		// Check intersection and setup vectors
		traceParam = GetSurfaceIntersection(character, GetGame().GetWorld(), hitPosition, Vector(0, -1, 0), distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);

		// Get Bone Matrix. If it's false, it's because of explosions or stuff like that
		if (character.GetBoneMatrix(nodeId, characterBoneMatrix))
		{

			correctedHitPosition = character.CoordToParent(characterBoneMatrix[3]);

			// Correct origin and projection
			origin = correctedHitPosition;
			projection = -traceParam.TraceNorm;
		}
		else
		{
			origin = character.GetOrigin() + Vector(0, distance / 4, 0);
			projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);
		}

		SpawnDecal(traceParam, EDecalType.BLOODPOOL, origin, projection, nearClip, farClip, angle, size, alphaTestValue, alphaMulValue);
	}

	void SpawnBloodTrail(IEntity character, vector hitPosition, float damage)
	{

		float distance = 2.0;
		float nearClip = 0;
		float farClip = 2.0;
		float angle;
		float size;

		// Print(damage);

		SCR_CharacterDamageManagerComponent charDamageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(character.FindComponent(SCR_CharacterDamageManagerComponent));
		SCR_CharacterControllerComponent charControllerComponent = SCR_CharacterControllerComponent.Cast(character.FindComponent(SCR_CharacterControllerComponent));
		;

		float speed = charControllerComponent.GetVelocity().Length();
		bool shouldBleed = charDamageManagerComponent.IsDamagedOverTime(EDamageType.BLEEDING) && (speed > 0);

		if (!shouldBleed)
			return;

		vector origin;
		vector projection;
		vector intersectionPosition;

		TraceParam traceParam = GetSurfaceIntersection(character, GetGame().GetWorld(), hitPosition, Vector(0, -1, 0), distance, TraceFlags.WORLD | TraceFlags.ENTS, intersectionPosition);
		origin = character.GetOrigin() + Vector(0, distance / 4, 0);
		projection = -traceParam.TraceNorm;

		size = Math.RandomFloatInclusive(0.1, damage / 200);
		angle = Math.RandomFloatInclusive(-360, 360);

		SpawnDecal(traceParam, EDecalType.DROPLETS, origin, projection, nearClip, farClip, angle, size, -1, -1, -1);
	}

	void AnimateDecals()
	{
		Print("Animate Decal");

		foreach (int index, DecalInformation dInfo : decalsSpawned)
		{
			DecalBaseInfo dBaseInfo = dInfo.decalBaseInfo;
			DecalPositionInfo dPositionInfo = dInfo.decalPositionInfo;
			MaterialInfo dMaterialInfo = dInfo.materialInfo;

			Decal d = dBaseInfo.decal;
			int currentFrame = dBaseInfo.currentFrame;

			array<ResourceName> refResources = materialsMap.Get(dBaseInfo.type);

			// todo make this constant
			float maxAlphaMul = 5;
			float minAlphaTest = 0.1;
			// settings = MCF_SettingsManager.GetModSettings(ABL_MOD_ID);

			if (dMaterialInfo.alphaMul < maxAlphaMul)
			{

				// Init temp variables
				ResourceName materialResourceName;
				Material currentMaterial;
				TraceParam traceParam = dPositionInfo.traceParam;

				float modifiedAlphaMul;
				float modifiedAlphaTest;
				float minimumAlphaMulChange;
				float maximumAlphaMulChange;
				float minimumAlphaTestChange;
				float maximumAlphaTestChange;

				if (d)
					GetGame().GetWorld().RemoveDecal(d);

				if (traceParam.TraceEnt)
				{
					materialResourceName = refResources[dMaterialInfo.indexAlpha];
					currentMaterial = Material.GetMaterial(materialResourceName);

					switch (dBaseInfo.type)
					{
					case EDecalType.BLOODPOOL:
					{
						minimumAlphaMulChange = 0.0002; // settings.Get("bloodpoolMinimumAlphaMulChange").ToFloat();
						maximumAlphaMulChange = 0.02;	// settings.Get("bloodpoolMaximumAlphaMulChange").ToFloat();
						minimumAlphaTestChange = 0;
						maximumAlphaTestChange = 0;
						break;
					}
					case EDecalType.WALLSPLATTER:
					{
						minimumAlphaMulChange = 0.0001;	 // settings.Get("wallsplatterMinimumAlphaMulChange").ToFloat();
						maximumAlphaMulChange = 0.02;	 // settings.Get("wallsplatterMaximumAlphaMulChange").ToFloat();
						minimumAlphaTestChange = 0.0001; // settings.Get("wallsplatterMinimumAlphaTestChange").ToFloat();
						maximumAlphaTestChange = 0.02;	 // settings.Get("wallsplatterMaximumAlphaTestChange").ToFloat();
						break;
					}
					}

					modifiedAlphaMul = dMaterialInfo.alphaMul + Math.RandomFloat(minimumAlphaMulChange, maximumAlphaMulChange);
					currentMaterial.SetParam("AlphaMul", modifiedAlphaMul);

					if (dMaterialInfo.alphaTest > minAlphaTest)
					{
						modifiedAlphaTest = dMaterialInfo.alphaTest - Math.RandomFloat(minimumAlphaTestChange, maximumAlphaTestChange);
						currentMaterial.SetParam("AlphaTest", modifiedAlphaTest);
					}
					else
						modifiedAlphaTest = dMaterialInfo.alphaTest;

					dMaterialInfo.alphaMul = modifiedAlphaMul;
					dMaterialInfo.alphaTest = modifiedAlphaTest;

					World tmpWorld = GetGame().GetWorld();
					Decal newDecal = tmpWorld.CreateDecal(traceParam.TraceEnt, dPositionInfo.originPosition, dPositionInfo.projectionDirection, 0, 2, dBaseInfo.rotation, dBaseInfo.size, 1, materialResourceName, -1, materialColor);

					dBaseInfo.decal = newDecal;
					dBaseInfo.currentFrame = currentFrame;
					decalsSpawned.Set(index, dInfo); // reset it... not sure if it's needed tbh
				}
			}
			else
			{
				decalsSpawned.Remove(index);
			}
		}
	}

	float SelectBloodpoolAngle(inout vector origin)
	{
		float tmpAngle;
		int randomNumber = Math.RandomIntInclusive(0, 2);

		// todo not sure if this is needed anymore
		switch (randomNumber)
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

	// Weapon splatters
	void GenerateWeaponSplatters(IEntity currentChar)
	{

		// Settings
		float farClipWeapon = 2;
		float nearClipWeapon = 0;
		int maxDecalsPlayerWeapon = 6;
		bool debugSpheres = 0; // settings.Get("debugSpheres").ToInt();

		// Other characters
		int maxDecalsPerChar = 2;
		ManageWeaponDecalsStack(currentChar, currentCharacterDecals, nearClipWeapon, farClipWeapon, maxDecalsPerChar);

		// Player Weapon
		PlayerManager pMan = GetGame().GetPlayerManager();
		SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		IEntity currentPlayer = m_playerController.GetMainEntity();
		vector playerTransform[4];
		currentPlayer.GetTransform(playerTransform);

		vector originCurrentCharacter = currentChar.GetOrigin();

		if (vector.Distance(playerTransform[3], originCurrentCharacter) < 3)
			ManageWeaponDecalsStack(currentPlayer, currentPlayerDecals, nearClipWeapon, farClipWeapon, maxDecalsPlayerWeapon, debugSpheres);
	}

	void ManageWeaponDecalsStack(IEntity owner, array<DecalWrapper> stack, float ncWeapon, float fcWeapon, int maxDecals, bool debugSpheres = false)
	{
		int weaponBloodColor = Color.FromRGBA(16, 0, 0, 255).PackToInt(); // move this away
		int count = stack.Count();

		if (count >= maxDecals)
		{
			int index = Math.RandomIntInclusive(0, stack.Count() - 1);
			// Print("Removing element " + index);
			DecalWrapper tmpWrapper = stack.Get(index);
			Decal tmpDecal = tmpWrapper.wrappedDecal;
			if (tmpDecal)
			{
				GetGame().GetWorld().RemoveDecal(tmpDecal);
				stack.Remove(index);
			}
		}

		// Tries to generate a decal
		count = stack.Count();
		if (count < maxDecals)
		{

			vector leftHandTransform[4];
			int nodeLeftHand = 2089750091;
			owner.GetBoneMatrix(nodeLeftHand, leftHandTransform);

			vector tmpTransformHand = leftHandTransform[3];
			tmpTransformHand[0] = tmpTransformHand[0]; //+ diffOriginX;
			tmpTransformHand[1] = tmpTransformHand[1]; //+ diffOriginY;
			tmpTransformHand[2] = tmpTransformHand[2]; //+ diffOriginZ;

			vector origin = owner.CoordToParent(tmpTransformHand);
			vector projection = origin;

			World tmpWorld = GetGame().GetWorld();
			DecalWrapper newTmpWrapperLeft = DecalWrapper(tmpWorld.CreateDecal(owner, origin, projection, 0, 2, 0, 1, 1, weaponSplatterMaterial, -1, weaponBloodColor));
			stack.Insert(newTmpWrapperLeft);
			// if(debugSpheres)
			//	MCF_Debug.DrawSphereAtPos(origin, COLOR_RED);
		}
	}

	static void CleanWeapon()
	{

		// todo spherecast and get near decals.
		// Print(previousPlayerWeaponDecal);
		// Print(currentPlayerDecals.Count());

		int count = currentPlayerDecals.Count();

		foreach (DecalWrapper decWrapper : currentPlayerDecals)
		{
			Decal tmpDecal = decWrapper.wrappedDecal;

			if (tmpDecal)
			{
				// Print("Removing decal: " + tmpDecal);
				SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
				IEntity currentPlayer = m_playerController.GetMainEntity();
				// SCR_CharacterControllerComponent.Cast(currentPlayer.FindComponent(SCR_CharacterControllerComponent)).SetInspectionMode(true);
				GetGame().GetWorld().RemoveDecal(tmpDecal); // doesn't automatically destroy the pointer
			}
		}

		currentPlayerDecals.Clear();
	}

	// Helpers
	static TraceParam GetSurfaceIntersection(IEntity owner, World m_world, vector origin, vector direction, float distance, int flags, out vector intersectionPosition)
	{
		auto param = new TraceParam();
		param.Start = origin;
		param.End = origin + direction * distance;
		param.Flags = flags;
		param.Exclude = owner;
		float intersectionDistance = m_world.TraceMove(param, NULL) * distance;
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

private
	bool isTerrainOnly;

	void DecalBaseInfo(Decal p_decal, EDecalType p_type, int p_currentFrame, float p_size, int p_rotation, int p_currentAlphaMul)
	{
		this.decal = p_decal;
		this.type = p_type;
		this.currentFrame = p_currentFrame;
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

	void DecalPositionInfo(TraceParam tf, vector originPos, vector projDir)
	{
		this.traceParam = tf;

		this.originPosition = originPos;
		this.projectionDirection = projDir;
	}

}

class MaterialInfo
{
	float alphaMul;
	float alphaTest;

	int indexAlpha; // to be used only with alpha blended maps not normal animated decals

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

enum EDecalType {
	BLOODPOOL,
	WALLSPLATTER,
	SINGLE_FRAME_GENERIC_SPLATTER,
	DROPLETS
}

class BloodTrailInfo : TrackDecalInfo
{
};