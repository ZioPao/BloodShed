modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	ref map<string, string> ablSettings;
	
	const string ABL_FileNameJson = "ABL_Settings.json";
	const string ABL_MOD_ID = "59951797A291CA02";				//it's probably possible to get this in a better way but ok
	
	IEntity ownerChar;
	bool alreadyDestroyed = false;
	World worldTmp;

	const int MAX_DECALS_PER_CHAR = 2;
	const int MAX_DECALS_PLAYER_WEAPON = 6;
	
	ref static array<ref DecalWrapper> currentPlayerDecals;
	ref array<ref DecalWrapper> currentCharacterDecals;
	ref static array<ref Shape> dbgShapes;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		ownerChar = owner;
		auto world = owner.GetWorld();
		
		
		currentCharacterDecals = new ref array<ref DecalWrapper>();
		
		if (!currentPlayerDecals)
			currentPlayerDecals = new array<ref DecalWrapper>();
		
		worldTmp = GetGame().GetWorld();
	////////////////////////////////////////////////////////////////////////////////////////////////
			//Settings initialization stuff 
			MCF_SettingsManager ABL_mcfSettingsManager = MCF_SettingsManager.GetInstance();
	
			OrderedVariablesMap ablVariablesMap = new OrderedVariablesMap();
			
			ablVariablesMap.Set("waitTimeBetweenFrames", new VariableInfo("Wait Times between frames (in seconds)", "0.1"));
			ablVariablesMap.Set("diffOriginX", new VariableInfo("Diff Origin X (TEST)", "0"));
			ablVariablesMap.Set("diffOriginY", new VariableInfo("Diff Origin Y (TEST)", "0"));
			ablVariablesMap.Set("diffOriginZ", new VariableInfo("Diff Origin Z (TEST)", "0"));
			ablVariablesMap.Set("nearClip", new VariableInfo("Near Clip (TEST)", "0"));
			ablVariablesMap.Set("farClip", new VariableInfo("Far Clip (TEST)", "5"));
			ablVariablesMap.Set("testProjY", new VariableInfo("Test Diff Test Proj", "0"));
	
			if (!ABL_mcfSettingsManager.GetJsonManager(ABL_MOD_ID))
			{
				ablSettings = ABL_mcfSettingsManager.Setup(ABL_MOD_ID, ABL_FileNameJson, ablVariablesMap);
			}
			else if (!ablSettings)
			{
				ablSettings = ABL_mcfSettingsManager.GetModSettings(ABL_MOD_ID);
				ABL_mcfSettingsManager.GetJsonManager(ABL_MOD_ID).SetUserHelpers(ablVariablesMap);
				
			}
			
	
			//////////////////////////////////////////////////////////////////////////////////////////////////
		
		
		dbgShapes = new array<ref Shape>();
	}

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
		super.OnDamage(type, damage, pHitZone, instigator, hitTransform, speed, colliderID, nodeID);
			
		ABL_AnimatedDecalManager tempManager;		//todo move this away
		tempManager = ABL_AnimatedDecalManager.GetInstance();
		
		
		
		ablSettings = MCF_SettingsManager.GetInstance().GetModSettings("59951797A291CA02");


		array<string> boneNames = new array<string>();
		ownerChar.GetBoneNames(boneNames);
		
		//we've got the local node id, we need the external one though. So.
		vector testVec[4];
		vector test1[4];
		
		int correctBoneIndex
		int correctNodeId;

		int colliderDescriptorIndex = pHitZone.GetColliderDescriptorIndex(colliderID);

		pHitZone.TryGetColliderDescription(ownerChar, colliderDescriptorIndex, test1, correctBoneIndex, correctNodeId);
		
		
		if (!tempManager)
			tempManager = ABL_AnimatedDecalManager.Cast(GetGame().SpawnEntity(ABL_AnimatedDecalManager, GetGame().GetWorld(), null));
			
		
		Print(pHitZone.GetName());
		if (hitTransform[0].Length() != 0)
		{
			if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
			{
				//Print("Start blood");
				GetGame().GetCallqueue().CallLater(tempManager.StartNewAnimation, 2000, false, ownerChar, hitTransform[0], hitTransform[1], EDecalType.BLOODPOOL, true, 1.5, correctNodeId);
	
				//tempManager.StartNewAnimation(ownerChar, hitTransform[0],  hitTransform[1], EDecalType.BLOODPOOL, true);
				alreadyDestroyed = true;		//only once
			}
			else if (damage > 20.0)
				tempManager.StartNewAnimation(ownerChar,  hitTransform[0],  hitTransform[1], EDecalType.GENERIC_SPLATTER, false, 0.0, correctNodeId);

			// Manages splatters on weapons 
			PlayerManager pMan = GetGame().GetPlayerManager();
			SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			IEntity currentPlayer = m_playerController.GetMainEntity();
			vector playerTransform[4];

			currentPlayer.GetTransform(playerTransform);
			//Print("Applying Decal on damaged entity");
			ManageDecalStack(currentCharacterDecals, ownerChar, hitTransform[0], hitTransform[1], 0, 2, MAX_DECALS_PER_CHAR);

			vector originChar = ownerChar.GetOrigin();
			
			//reset it
			if (vector.Distance(playerTransform[3], originChar) < 15)
			{
				float farClipPlayerWeaponDecal = vector.Distance(playerTransform[3], originChar);
				
				//Print(testVec);
				//Print(originPlayer);
				vector normal = playerTransform[0];		//1st one is the normal I guess?
				Print("Applying Decals on Player Weapon");
				
				
				float nearClip = ablSettings.Get("nearClip").ToFloat();
				float farClip = ablSettings.Get("farClip").ToFloat();

				
				
				
				ManageDecalStack(currentPlayerDecals, currentPlayer, hitTransform[0], hitTransform[1], nearClip, farClip,MAX_DECALS_PLAYER_WEAPON, true);
				Print("________________________");
				
				
				
			}
		}
	}

	
	
	
	void ManageDecalStack(array<ref DecalWrapper> stack, IEntity owner, vector hitPosition, vector hitDirection, float nearClip, float farClip, int maxDecals, bool doubleSpawn = false)
	{
		int materialColor = Color.FromRGBA(16, 0, 0,255).PackToInt();		//move this away

		//float distance = 3;
		//if(maxDecals == 6)
		//{
	//		Print(hitPosition);
	//	//	Print(hitDirection);
	//	}
			//Print("stop");
			
		auto param = new TraceParam();
  		param.Start = hitPosition;
  		param.End = hitPosition + hitDirection * farClip;
  		param.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
  		param.Exclude = owner;
		float intersectionDistance = worldTmp.TraceMove(param, NULL) * farClip;
		vector intersectionPosition = hitPosition + (hitDirection * intersectionDistance);
		
		
		//set dynamic stuff here 
		ablSettings = MCF_SettingsManager.GetInstance().GetModSettings("59951797A291CA02");
		float diffOriginX = ablSettings.Get("diffOriginX").ToFloat();
		float diffOriginY = ablSettings.Get("diffOriginY").ToFloat();
		float diffOriginZ = ablSettings.Get("diffOriginZ").ToFloat();
		
		vector origin = hitPosition;
		
		/*
		if (origin[0] < 0)
			origin[0] = origin[0] - diffOrigin;
		else
			origin[0] = origin[0] + diffOrigin;
		
		
		if (origin[2] < 0)
			origin[2] = origin[2] - diffOrigin;
		else 
			origin[2] = origin[2] +diffOrigin;
		*/
		
		//origin[1] = origin[1] + 1;		//just set it higher ?
		vector projection = - hitDirection;

		if (projection.Length() == 0)
			projection = origin;
		
		
		
		projection = origin;		//tmp
		
		float rotation = Math.RandomFloatInclusive(-360, 360);
		
		//if (maxDecals == 6)
		//	ABL_AnimatedDecalManager.GetSurfaceIntersection(owner, worldTmp, orig, direct, 5, TraceFlags.ENTS, projection);
		ResourceName tempMaterial = "{82129FA9BA80D8F4}materials/WeaponBloodSecondTry.emat";

		
		
		
		int count = stack.Count();
		//Print("Current count: " + count);
		if (count >= maxDecals)
		{
			int index = Math.RandomIntInclusive(0, stack.Count() - 1);
			//Print("Removing element " + index);
			DecalWrapper tmpWrapper = stack.Get(index);
			Decal tmpDecal = tmpWrapper.wrappedDecal;
			if (tmpDecal)
			{
				worldTmp.RemoveDecal(tmpDecal);
				stack.Remove(index);
			}
			
			if (doubleSpawn)
			{
				index = Math.RandomIntInclusive(0, stack.Count() - 1);
				//Print("Removing another element " + index);
				tmpWrapper = stack.Get(index);
				tmpDecal = tmpWrapper.wrappedDecal;
				if (tmpDecal)
				{
					worldTmp.RemoveDecal(tmpDecal);
					stack.Remove(index);
				}
			}
				
	
		}
		
		
		count = stack.Count();
		//Print("Count after removing " + count);
		if (count < maxDecals)
		{


			// This works when he's on the ground squirming. 
			
			
			//float testProjY = ablSettings.Get("testProjY").ToFloat();
			
			//vector testProj = owner.GetOrigin();
			//testProj[1] = testProj[1] + 1;
			
			//if (maxDecals == MAX_DECALS_PLAYER_WEAPON)
			//{
			//	Print("Creating splatter");
			//	Print(origin);
		//		Print(projection);
			//	//Print(testProj);
				//Print("_____________");
			//}
			
			
			
			//GetBoneMAtrix
			
			
			vector leftHandTransform[4];
			vector rightHandTransform[4];
			int nodeLeftHand = 2089750091;
			int nodeRightHand = 2889608574;
			
			
			owner.GetBoneMatrix(nodeLeftHand, leftHandTransform);
			owner.GetBoneMatrix(nodeRightHand, rightHandTransform);
			
			
			
			vector tmpTransformHand = leftHandTransform[3];
			//if (tmpOrigin[0] < 0)
			//	tmpOrigin[0] = tmpOrigin[0] - diffOriginX;
			//else 
			tmpTransformHand[0] = tmpTransformHand[0] + diffOriginX;

			//if (tmpOrigin[1] < 0)
			//	tmpOrigin[1] = tmpOrigin[1] - diffOriginY;
			//else 
			tmpTransformHand[1] = tmpTransformHand[1] + diffOriginY;
			
			//if (tmpOrigin[2] < 0)
			//	tmpOrigin[2] = tmpOrigin[2] - diffOriginZ;
			//else 
			tmpTransformHand[2] = tmpTransformHand[2] + diffOriginZ;
			
			vector tmpOrigin = owner.CoordToParent(tmpTransformHand);
			


			
			
			
			//tmpOrigin = vector.Lerp(owner.CoordToParent(leftHandTransform[3]), tmpOrigin, 0.5);
			vector tmpProjection = tmpOrigin;

			
			//DecalWrapper(worldTmp.CreateDecal(owner, origin, testProj, 1, 5, 0, 1, 1, tempMaterial, -1, materialColor));
			//DecalWrapper(worldTmp.CreateDecal(owner, origin, testProj, 2, 6, 0, 1, 1, tempMaterial, -1, materialColor));
			DecalWrapper newTmpWrapperLeft = DecalWrapper(worldTmp.CreateDecal(owner, tmpOrigin, tmpProjection, nearClip, farClip, 0, 1, 1, tempMaterial, -1, materialColor));
			stack.Insert(newTmpWrapperLeft);
			
			if (doubleSpawn)
			{
				
				vector tmpOrigin2 = owner.CoordToParent(rightHandTransform[2]);
				
				tmpOrigin2[0] = tmpOrigin2[0] + diffOriginX;
				tmpOrigin2[1] = tmpOrigin[1] + diffOriginY;
				tmpOrigin2[2] = tmpOrigin2[2] + diffOriginZ;
				vector tmpProjection2 = tmpOrigin2;
				
				
				Debug_DrawSphereAtPos(tmpOrigin, COLOR_RED);
				Print(tmpOrigin);
				//Debug_DrawSphereAtPos(tmpOrigin2, COLOR_RED);

				
				
					
				DecalWrapper newTmpWrapperRight = DecalWrapper(worldTmp.CreateDecal(owner, tmpOrigin2, tmpProjection2, nearClip, farClip, 0, 1, 1, tempMaterial, -1, materialColor));
				stack.Insert(newTmpWrapperRight);
			}
			

			
			
			
			
			
			

		// 	DecalWrapper newTmpWrapper2 = DecalWrapper(worldTmp.CreateDecal(owner, origin, testProj, 3, 6, 0, 1, 1, tempMaterial, -1, materialColor));
//		stack.Insert(newTmpWrapper2);

			//DecalWrapper newTmpWrapper3= DecalWrapper(worldTmp.CreateDecal(owner, origin, testProj, 4, 9, 0, 1, 1, tempMaterial, -1, materialColor));
			//stack.Insert(newTmpWrapper3);

			//DecalWrapper newTmpWrapper = DecalWrapper(worldTmp.CreateDecal(owner, origin, testProj, nearClip, farClip, 0, 1, 1, tempMaterial, -1, materialColor));
//			stack.Insert(newTmpWrapper);
		}

		
	}
	
	
	//------------------------------------------------------------------------------------------------
	private void Debug_DrawSphereAtPos(vector pos, int color)
	{
		vector matx[4];
		Math3D.MatrixIdentity4(matx);
		matx[3] = pos;
		int shapeFlags = ShapeFlags.DEFAULT;
		Shape s = Shape.CreateSphere(color, shapeFlags, pos, 0.05);
		s.SetMatrix(matx);
		dbgShapes.Insert(s);
	}
	
	
	
	static void CleanWeapon()
	{
		
		//todo spherecast and get near decals.
		//Print(previousPlayerWeaponDecal);
		Print(currentPlayerDecals.Count());
		
		

		int count = currentPlayerDecals.Count();
		
		foreach(DecalWrapper decWrapper : currentPlayerDecals)
		{
			Decal tmpDecal = decWrapper.wrappedDecal;
			
			if (tmpDecal)
			{
				Print("Removing decal: " + tmpDecal);
				SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
				IEntity currentPlayer = m_playerController.GetMainEntity();
				SCR_CharacterControllerComponent.Cast(currentPlayer.FindComponent(SCR_CharacterControllerComponent)).SetInspectionMode(true);
				GetGame().GetWorld().RemoveDecal(tmpDecal);		//doesn't automatically destroy the pointer

			}
		}
		
		currentPlayerDecals.Clear();

	}
	
	


	

}





class TestClass
{

	// generate perlin noise 
	
	// write it to edds file... ttttttthat we don't have any idea how to do it 
	
	//  register it
		//class GeneratedResources
	//{
	//	proto bool RegisterResource(string absPath, out ResourceName resourceName);
	//
	//	private void GeneratedResources();
	//	private void ~GeneratedResources();
	//}

	// read it
	
	/*
		// ! saves perlin in an image for debug purposes
	void PerlinDebug()
	{
			string filePath = "d:\\test.dds";
			ref array<int> data = new array<int>;
		
			const int WIDTH = 1024;
			const int HEIGHT = 1024;
		
			for (int y = 0; y < HEIGHT; y++) for (int x = 0; x < WIDTH; x++)
			{
				int count = x * y;
			
				float perlinVal = Math.PerlinNoise(x/m_fPerlinFrequency, y/m_fPerlinFrequency);
				//Print(perlinVal);
					
				int pixel = ARGB(255, perlinVal * 255, perlinVal * 255, perlinVal * 255 );
				data.Insert(pixel);
			}

			// save dds to file
			if (TexTools.SaveImageData(filePath, WIDTH, HEIGHT, data) == false)
			{
				//Print("Can't save image", LogLevel.ERROR);
				return;
			}
	}
	*/		
	
	//FUCK YOU FOUND YOU FUCK YOU

	//delete it... jesus what a shitshow
}




class Queue<Class T>
{
	protected ref array<ref T> m_aArray;
	
	//-----------------------------------------------------------------------------------------------------------
	//! Push an item to the end of the stack
	void Push(T item) 
	{
		m_aArray.Insert(item);
		
		
		int length = m_aArray.Count();
		
		if (length >= 1)
		{
		
		
			
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------
	//! Pop an item from the end of the stack (or null if none)
	T Pop()
	{
		int length = m_aArray.Count();
		if (length >= 1)
		{
			int index = length-1;
			
			ref T poppedItem = m_aArray[index];
			m_aArray.Remove(index);
			
			return poppedItem;
		}
		
		return null;
	}
	
	//-----------------------------------------------------------------------------------------------------------
	//! Returns true if stack is empty.
	bool IsEmpty()
	{
		return (m_aArray.Count() == 0);
	}
	
	//-----------------------------------------------------------------------------------------------------------
	//! Returns the count of elements stored in this stack.
	int Count()
	{
		return m_aArray.Count();
	}
	
	//-----------------------------------------------------------------------------------------------------------
	//! Create an empty stack, initialize variables
	void SCR_Stack()
	{
		m_aArray = new ref array<ref T>();
	}
	
	//-----------------------------------------------------------------------------------------------------------
	//! Cleanup, release variables
	void ~SCR_Stack()
	{
		if (m_aArray)
		{
			m_aArray.Clear();
			m_aArray = null;			
		}
	}
};





class DecalWrapper
{
	Decal wrappedDecal;
	
	
	void DecalWrapper(Decal d)
	{
		wrappedDecal = d;
	
	}

}