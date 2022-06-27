class ABL_AnimatedDecalManagerClass : GenericEntityClass
{}



//todo implement weapon cleaning 



class ABL_AnimatedDecalManager : GenericEntity
{
	
	ref map<EDecalType, ref array<ResourceName>> animationMaterials;
	ref map<int, ref DecalInformation> decalsSpawned;
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
		animationMaterials.Insert(EDecalType.GENERIC_SPLATTER, {"{5B7FA62DF33CB204}materials/wall_splatter/materials/000.emat","{AF77E1B5FEE1DA70}materials/wall_splatter/materials/001.emat","{F19FC8F6416C547F}materials/wall_splatter/materials/002.emat","{05978F6E4CB13C0B}materials/wall_splatter/materials/003.emat","{4C4F9A713E774861}materials/wall_splatter/materials/004.emat","{B847DDE933AA2015}materials/wall_splatter/materials/005.emat","{E6AFF4AA8C27AE1A}materials/wall_splatter/materials/006.emat","{12A7B33281FAC66E}materials/wall_splatter/materials/007.emat","{751FDE9469AB46CE}materials/wall_splatter/materials/008.emat","{8117990C64762EBA}materials/wall_splatter/materials/009.emat","{9CB336B0066AF108}materials/wall_splatter/materials/010.emat","{68BB71280BB7997C}materials/wall_splatter/materials/011.emat","{3653586BB43A1773}materials/wall_splatter/materials/012.emat","{C25B1FF3B9E77F07}materials/wall_splatter/materials/013.emat","{8B830AECCB210B6D}materials/wall_splatter/materials/014.emat","{7F8B4D74C6FC6319}materials/wall_splatter/materials/015.emat","{216364377971ED16}materials/wall_splatter/materials/016.emat","{D56B23AF74AC8562}materials/wall_splatter/materials/017.emat","{B2D34E099CFD05C2}materials/wall_splatter/materials/018.emat","{46DB099191206DB6}materials/wall_splatter/materials/019.emat","{961666FDB07A028F}materials/wall_splatter/materials/020.emat","{621E2165BDA76AFB}materials/wall_splatter/materials/021.emat","{3CF60826022AE4F4}materials/wall_splatter/materials/022.emat","{C8FE4FBE0FF78C80}materials/wall_splatter/materials/023.emat","{81265AA17D31F8EA}materials/wall_splatter/materials/024.emat","{752E1D3970EC909E}materials/wall_splatter/materials/025.emat","{2BC6347ACF611E91}materials/wall_splatter/materials/026.emat","{DFCE73E2C2BC76E5}materials/wall_splatter/materials/027.emat","{B8761E442AEDF645}materials/wall_splatter/materials/028.emat","{4C7E59DC27309E31}materials/wall_splatter/materials/029.emat","{51DAF660452C4183}materials/wall_splatter/materials/030.emat","{A5D2B1F848F129F7}materials/wall_splatter/materials/031.emat","{FB3A98BBF77CA7F8}materials/wall_splatter/materials/032.emat","{0F32DF23FAA1CF8C}materials/wall_splatter/materials/033.emat","{46EACA3C8867BBE6}materials/wall_splatter/materials/034.emat","{B2E28DA485BAD392}materials/wall_splatter/materials/035.emat","{EC0AA4E73A375D9D}materials/wall_splatter/materials/036.emat","{1802E37F37EA35E9}materials/wall_splatter/materials/037.emat","{7FBA8ED9DFBBB549}materials/wall_splatter/materials/038.emat","{8BB2C941D266DD3D}materials/wall_splatter/materials/039.emat","{835CC666DC5BE581}materials/wall_splatter/materials/040.emat","{775481FED1868DF5}materials/wall_splatter/materials/041.emat","{29BCA8BD6E0B03FA}materials/wall_splatter/materials/042.emat","{DDB4EF2563D66B8E}materials/wall_splatter/materials/043.emat","{946CFA3A11101FE4}materials/wall_splatter/materials/044.emat","{6064BDA21CCD7790}materials/wall_splatter/materials/045.emat","{3E8C94E1A340F99F}materials/wall_splatter/materials/046.emat","{CA84D379AE9D91EB}materials/wall_splatter/materials/047.emat","{AD3CBEDF46CC114B}materials/wall_splatter/materials/048.emat","{5934F9474B11793F}materials/wall_splatter/materials/049.emat","{449056FB290DA68D}materials/wall_splatter/materials/050.emat","{B098116324D0CEF9}materials/wall_splatter/materials/051.emat","{EE7038209B5D40F6}materials/wall_splatter/materials/052.emat","{1A787FB896802882}materials/wall_splatter/materials/053.emat","{53A06AA7E4465CE8}materials/wall_splatter/materials/054.emat","{A7A82D3FE99B349C}materials/wall_splatter/materials/055.emat","{F940047C5616BA93}materials/wall_splatter/materials/056.emat","{0D4843E45BCBD2E7}materials/wall_splatter/materials/057.emat","{6AF02E42B39A5247}materials/wall_splatter/materials/058.emat","{9EF869DABE473A33}materials/wall_splatter/materials/059.emat","{4E3506B69F1D550A}materials/wall_splatter/materials/060.emat","{BA3D412E92C03D7E}materials/wall_splatter/materials/061.emat","{E4D5686D2D4DB371}materials/wall_splatter/materials/062.emat","{10DD2FF52090DB05}materials/wall_splatter/materials/063.emat"});
		
		alphaNoise = {"{65CDA7EB00B1455C}TestAlpha/001.edds","{3B258EA8BF3CCB53}TestAlpha/002.edds","{CF2DC930B2E1A327}TestAlpha/003.edds","{86F5DC2FC027D74D}TestAlpha/004.edds","{72FD9BB7CDFABF39}TestAlpha/005.edds","{2C15B2F472773136}TestAlpha/006.edds","{D81DF56C7FAA5942}TestAlpha/007.edds","{BFA598CA97FBD9E2}TestAlpha/008.edds","{4BADDF529A26B196}TestAlpha/009.edds","{560970EEF83A6E24}TestAlpha/010.edds","{A2013776F5E70650}TestAlpha/011.edds","{FCE91E354A6A885F}TestAlpha/012.edds","{08E159AD47B7E02B}TestAlpha/013.edds","{41394CB235719441}TestAlpha/014.edds","{B5310B2A38ACFC35}TestAlpha/015.edds","{EBD922698721723A}TestAlpha/016.edds","{1FD165F18AFC1A4E}TestAlpha/017.edds","{7869085762AD9AEE}TestAlpha/018.edds","{8C614FCF6F70F29A}TestAlpha/019.edds","{5CAC20A34E2A9DA3}TestAlpha/020.edds","{A8A4673B43F7F5D7}TestAlpha/021.edds","{F64C4E78FC7A7BD8}TestAlpha/022.edds","{024409E0F1A713AC}TestAlpha/023.edds","{4B9C1CFF836167C6}TestAlpha/024.edds","{BF945B678EBC0FB2}TestAlpha/025.edds","{E17C7224313181BD}TestAlpha/026.edds","{157435BC3CECE9C9}TestAlpha/027.edds","{72CC581AD4BD6969}TestAlpha/028.edds","{86C41F82D960011D}TestAlpha/029.edds","{9B60B03EBB7CDEAF}TestAlpha/030.edds","{6F68F7A6B6A1B6DB}TestAlpha/031.edds","{3180DEE5092C38D4}TestAlpha/032.edds","{C588997D04F150A0}TestAlpha/033.edds","{8C508C62763724CA}TestAlpha/034.edds","{7858CBFA7BEA4CBE}TestAlpha/035.edds","{26B0E2B9C467C2B1}TestAlpha/036.edds","{D2B8A521C9BAAAC5}TestAlpha/037.edds","{B500C88721EB2A65}TestAlpha/038.edds","{41088F1F2C364211}TestAlpha/039.edds","{49E68038220B7AAD}TestAlpha/040.edds","{BDEEC7A02FD612D9}TestAlpha/041.edds","{E306EEE3905B9CD6}TestAlpha/042.edds","{170EA97B9D86F4A2}TestAlpha/043.edds","{5ED6BC64EF4080C8}TestAlpha/044.edds","{AADEFBFCE29DE8BC}TestAlpha/045.edds","{F436D2BF5D1066B3}TestAlpha/046.edds","{003E952750CD0EC7}TestAlpha/047.edds","{6786F881B89C8E67}TestAlpha/048.edds","{938EBF19B541E613}TestAlpha/049.edds","{8E2A10A5D75D39A1}TestAlpha/050.edds","{7A22573DDA8051D5}TestAlpha/051.edds","{24CA7E7E650DDFDA}TestAlpha/052.edds","{D0C239E668D0B7AE}TestAlpha/053.edds","{991A2CF91A16C3C4}TestAlpha/054.edds","{6D126B6117CBABB0}TestAlpha/055.edds","{33FA4222A84625BF}TestAlpha/056.edds","{C7F205BAA59B4DCB}TestAlpha/057.edds","{A04A681C4DCACD6B}TestAlpha/058.edds","{54422F844017A51F}TestAlpha/059.edds","{848F40E8614DCA26}TestAlpha/060.edds","{708707706C90A252}TestAlpha/061.edds","{2E6F2E33D31D2C5D}TestAlpha/062.edds","{DA6769ABDEC04429}TestAlpha/063.edds","{93BF7CB4AC063043}TestAlpha/064.edds"};
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
	
	
	static void SpawnSingleFrame(IEntity character, World world, vector hitPosition, vector hitDirection, ResourceName material)

	{
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
		array<ResourceName> tempFrames = animationMaterials.Get(type);
		
		
		
		int traceFlags;
		
		if (terrainOnly)
			traceFlags = TraceFlags.WORLD;
		else 
			traceFlags = TraceFlags.WORLD | TraceFlags.ENTS;
		

		//TEST differnet origin 
		vector mat[4];
			
			
			
		switch(type)
		{
			
			case EDecalType.BLOODPOOL:
			{
					
				if (character.GetBoneMatrix(nodeId, mat))
				{
					traceParam = GetSurfaceIntersection(character, m_world, hitPosition, Vector(0, -1, 0), distance, traceFlags, intersectionPosition);
					vector pos = character.CoordToParent(mat[3]);
					pos[2] = pos[2] + 0.5;
					origin = pos;
					projection = -traceParam.TraceNorm;
					
					angle = SelectBloodpoolAngle(origin);
				}
				else 
				{
					//cant find bone, should never happen?
					origin = character.GetOrigin() + Vector(0, 2.0 / 4, 0);			
		 			projection = vector.Lerp(-traceParam.TraceNorm, hitDirection, 0.5);
				}
			
				break;
			}
			case EDecalType.GENERIC_SPLATTER:
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
				break;
			}
			
			
		}
			
			
			
			

		if (traceParam.TraceEnt) 
		{			
			float size = Math.RandomFloatInclusive(1.0, 1.0 + sizeModifier);		//Doesn't seem random.... 
			ResourceName testAlphaBlend = "{4E301E96FBEBB515}testbloodalpha.emat";

			Material tmp = Material.GetOrLoadMaterial(testAlphaBlend, 0);
			
			//ResourceName tempAlpha = alphaNoise[Math.RandomIntInclusive(0, alphaNoise.Count())];
			
			int indexAlpha = Math.RandomIntInclusive(0, alphaNoise.Count() - 1);
			ResourceName tempAlpha = alphaNoise[indexAlpha];			//todo make this random

			tmp.SetParam("OpacityMap", tempAlpha);
			tmp.SetParam("NMOMap", tempAlpha);
			tmp.SetParam("BCRMap", tempAlpha);		//todo finish this and set it to some toher places
			tmp.SetParam("AlphaBlend", 0.55);
			tmp.SetParam("AlphaMul", 1);
			

			
			
			
			
			// Decal tmpDecal = m_world.CreateDecal(traceParam.TraceEnt, origin, projection, nearClip, farClip, angle, size, 1, tempFrames[0], -1, materialColor);
			Decal tmpDecal = m_world.CreateDecal(traceParam.TraceEnt, origin, projection, nearClip, farClip, angle, size, 1, testAlphaBlend, -1, materialColor);


			// try to insert it into the decalsSpawned map 
			int index = Math.RandomInt(-10000, 10000);
			
			while(decalsSpawned.Get(index))
				index = Math.RandomInt(-10000, 10000);
			
			DecalInformation tmpDecalInformation = new DecalInformation(tmpDecal, type, 1, traceParam, hitPosition, hitDirection, origin, projection, size, angle, 1, terrainOnly, indexAlpha); 
			//tmpDecalInformation.SetMaterialInfo(new MaterialInfo(0.55, 1));
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
					
					ResourceName testAlphaBlend = "{4E301E96FBEBB515}testbloodalpha.emat";
					
					Material tmp = Material.GetOrLoadMaterial(testAlphaBlend, 0);
					//tmp.SetParam("AlphaMul", 1.25);
					
					float modifiedAlphaMul = dInfo.currentAlphaMul + Math.RandomFloat(0.0001, 0.05);
					//float modifiedAlphaTest = dInfo.currentAlpha + Math.RandomFloat(0.0001, 0.02);
			
			//ResourceName tempAlpha = alphaNoise[Math.RandomIntInclusive(0, alphaNoise.Count())];
					ResourceName tempAlpha = alphaNoise[dInfo.indexAlpha];			//todo make this random

					tmp.SetParam("OpacityMap", tempAlpha);
					tmp.SetParam("NMOMap", tempAlpha);
					tmp.SetParam("BCRMap", tempAlpha);
					tmp.SetParam("AlphaBlend", 0.55);
					tmp.SetParam("AlphaMul", modifiedAlphaMul);
					
					
					//tmpSetParam("AlphaTest", modifiedAlphaTest
					
					dInfo.currentAlphaMul = modifiedAlphaMul; 
					//Print(modifiedAlphaMul);
					
					//tmp.SetParam("GBufferNormal", 1);
					//tmp.SetParam("NormalCombinePower",1.3 + Math.RandomFloat(-0.1, 0.1));
					//tmp.SetParam("NoDecals", 1);
					
					

					
					
					Decal newDecal = m_world.CreateDecal(traceParam.TraceEnt, dInfo.originPosition, dInfo.projectionDirection, nearClip, farClip, dInfo.rotation, dInfo.size, 1, testAlphaBlend, -1, materialColor);
					
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
	
	
	
	
	float SelectBloodpoolAngle(inout vector origin)
	{
		float tmpAngle;
		int randomNumber = Math.RandomIntInclusive(0,2);

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
	
	MaterialInfo matInfo;
	float indexAlpha;
	
	void DecalInformation( Decal d, EDecalType t, int cf, TraceParam tp, vector hp, vector hd, vector op, vector pd, float s, float r, float cam, bool to, float indexAlphaRandom)
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
		
		indexAlpha = indexAlphaRandom;
	}
	
	
	void SetMaterialInfo(MaterialInfo mi)
	{
		this.matInfo = mi;
	}
}


class MaterialInfo
{
	float alphaMul;
	float alphaTest;
	
	void MaterialInfo(float am, float at)
	{
		alphaMul = am;
		alphaTest = at;
	}
	

}

enum EDecalType
{
	BLOODPOOL,
	GENERIC_SPLATTER
}