










[WorkbenchPluginAttribute(name: "Perlin Texture Generator", category: "Pao's Plugins", wbModules: {"ResourceManager"}, awesomeFontCode: 0xf0c5)]
class ProceduralTexture : ResourceManagerPlugin
{
	

	
		
	[Attribute(defvalue: "1", uiwidget : UIWidgets.EditBox, desc: "Amount", category: "Settings")];
	int amount;
			
	[Attribute(defvalue: "1024", uiwidget : UIWidgets.EditBox, desc: "Size", category: "Settings")];
	int size;
	
	[Attribute(defvalue: "1", uiwidget : UIWidgets.EditBox, desc: "Modifier", category: "Settings")];
	float modifier;
	
	ResourceManager resourceManager;
	
	//perlin? 
	override void Run()
	{
		// Grab reference to ResourceManager 
		resourceManager = Workbench.GetModule(ResourceManager);
		if (!resourceManager) 
			return;
		

		Workbench.ScriptDialog("Stiffr", "Import multiple materials rapidly", this);
		

	}

	void RandomMapGenerator()
	{
		
		string absPath;
		string folder = "C:\\Users\\aless\\Documents\\My Games\\ArmaReforger\\addons\\PROJECTS\\Animated Bloodlust\\TestPerlin";
		
		Workbench.GetAbsolutePath(folder, absPath, false);

		ResourceName resourceID;
		int x_perlin; float y_perlin;

		ref array<int> data = new array<int>;

		//x_perlin = Math.RandomIntInclusive(30,100);
		
		for (int i = 0; i < amount; i++)
		{
			//x_perlin ++;
			data = new array<int>;

			//m_fPerlinFrequency = Math.RandomFloatInclusive(1,100);
			string filePath = absPath + "/" + i.ToString() + ".dds";
			for (int y = 0; y < size; y++) for (int x = 0; x < size; x++)
			{
				int count = x * y;
				
				//x_perlin = Math.RandomIntInclusive(1, 1000);
				//y_perlin= Math.RandomIntInclusive(40 100);

				//x_perlin = 100;
				
				
				//float perlinVal = Math.PerlinNoise(x/x_perlin, y/x_perlin);
				float perlinVal = Math.RandomGaussFloat(x/modifier, y/modifier);
				//Print(perlinVal);
					
				int pixel = ARGB(255, perlinVal * 255, perlinVal * 255, perlinVal * 255 );
				//pixel = AWHITE(pixel);
				data.Insert(pixel);
			}
	
			// save dds to file
			if (TexTools.SaveImageData(filePath, size, size, data) == false)
			{
					//Print("Can't save image", LogLevel.ERROR);
	
				//Print(filePath);
			}

		}
		
		
	}
	

	// Code which is executed when settings are accesed
	override void Configure()
	{
		Print("Test");

	}
	

	// This method is executed every time some new resource is registered
	override void OnRegisterResource(string absFileName, BaseContainer metaFile)
	{
		Print(absFileName);
	}
	
	
	// ButtonAttributes 
	[ButtonAttribute("Cancel")]
	void CancelButton()	 
	{
		return;
	
	}
	
	[ButtonAttribute("OK")]
	void OkButton() {
	
		RandomMapGenerator();
	}

}