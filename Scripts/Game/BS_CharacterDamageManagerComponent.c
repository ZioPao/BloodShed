modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	
	ref map<string, string> bsSettings;
	const string BS_FileNameJson = "BS_Settings.json";
	const string BS_MOD_ID = "59D925199B6E6BFD";			
	
	
	
	IEntity currentCharacter;
	bool alreadyDestroyed = false;
	float timerBetweenSplatters; 
	World world;

	

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		currentCharacter = owner;
		world = owner.GetWorld();

		
		
		////////////////////////////////////////////////////////////////////////////////
		OrderedVariablesMap bsVariablesMap = new OrderedVariablesMap();
		
		bsVariablesMap.Set("waitTimeBetweenFrames", new VariableInfo("Wait between frames", "0.033", EFilterType.TYPE_FLOAT));
		bsVariablesMap.Set("enableWeaponSplatters", new VariableInfo("Enable Weapon Splatters (Currently kinda broken)", "0", EFilterType.TYPE_FLOAT));
		
		
		bsVariablesMap.Set("bloodpoolMinimumAlphaMulChange", new VariableInfo("Alpha Mul Bloodpools - Min Random Change", "0.0002", EFilterType.TYPE_FLOAT));
		bsVariablesMap.Set("bloodpoolMaximumAlphaMulChange", new VariableInfo("Alpha Mul Bloodpools - Max Random Change", "0.03", EFilterType.TYPE_FLOAT));
			
		bsVariablesMap.Set("wallsplatterMinimumAlphaMulChange", new VariableInfo("Alpha Mul Wallsplatters - Min Random Change", "0.0001", EFilterType.TYPE_FLOAT));
		bsVariablesMap.Set("wallsplatterMaximumAlphaMulChange", new VariableInfo("Alpha Mul Wallsplatters - Max Random Change", "0.02", EFilterType.TYPE_FLOAT));
		
		bsVariablesMap.Set("wallsplatterMinimumAlphaTestChange", new VariableInfo("Alpha Test Wallsplatters - Min Random Change", "0.0001", EFilterType.TYPE_FLOAT));
		bsVariablesMap.Set("wallsplatterMaximumAlphaTestChange", new VariableInfo("Alpha Test Wallsplatters - Max Random Change", "0.02", EFilterType.TYPE_FLOAT));
	
			
		//bsVariablesMap.Set("maxAlphaMul", new VariableInfo("Alpha Test Maximum value", "5", EFilterType.TYPE_FLOAT));			//max 5
		//bsVariablesMap.Set("minAlphaTest", new VariableInfo("Alpha Test Minimum value", "0.1", EFilterType.TYPE_FLOAT));
		
		bsVariablesMap.Set("chanceStaticDecal", new VariableInfo("Chance of a static blood decal to appear (0 to 100)", "50", EFilterType.TYPE_FLOAT));

	
			
		bsVariablesMap.Set("maxDecalsPerChar", new VariableInfo("Max Decals per Character", "2", EFilterType.TYPE_INT));
		bsVariablesMap.Set("maxDecalsPlayerWeapon", new VariableInfo("Max Decals for Player Weapon", "4", EFilterType.TYPE_INT));
			
		bsVariablesMap.Set("bloodpoolSize", new VariableInfo("Bloodpol Size", "1.5", EFilterType.TYPE_FLOAT));
		bsVariablesMap.Set("wallsplatterSize", new VariableInfo("Wallsplatter Size", "1", EFilterType.TYPE_FLOAT));	
	
		if (!MCF_SettingsManager.GetJsonManager(BS_MOD_ID))
		{
			MCF_SettingsManager.Setup(BS_MOD_ID, BS_FileNameJson, bsVariablesMap);
		
		}
		else if (!bsSettings)
		{
			bsSettings = MCF_SettingsManager.GetModSettings(BS_MOD_ID);
			MCF_SettingsManager.GetJsonManager(BS_MOD_ID).SetUserHelpers(bsVariablesMap);		
		}
		
		
		

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
		

		BS_AnimatedBloodManager animatedBloodManager;		
		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();		
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimatedBloodManager.Cast(GetGame().SpawnEntity(BS_AnimatedBloodManager, GetGame().GetWorld(), null));
				

		int correctNodeId;
		int colliderDescriptorIndex = pHitZone.GetColliderDescriptorIndex(colliderID);
		pHitZone.TryGetColliderDescription(currentCharacter, colliderDescriptorIndex, null, null, correctNodeId);
			
	
			
		if (hitTransform[0].Length() != 0)
		{
				

			
			if (GetState() == EDamageState.DESTROYED && !alreadyDestroyed)
			{
				
				
				GetGame().GetCallqueue().CallLater(animatedBloodManager.SpawnGroundBloodpool, 2000, false, currentCharacter, hitTransform[0], hitTransform[1], correctNodeId);
				alreadyDestroyed = true;		//only once
			}
			else if (damage > 15.0)
			{
				animatedBloodManager.SpwanWallSplatter(currentCharacter,  hitTransform[0],  hitTransform[1]);
		
			}
			
			bsSettings = MCF_SettingsManager.GetModSettings(BS_MOD_ID);
			int enableWeaponSplatters = bsSettings.Get("enableWeaponSplatters").ToInt();
				
			if (enableWeaponSplatters == 1)
				animatedBloodManager.GenerateWeaponSplatters(currentCharacter);
			
				
			float chanceStaticDecal = bsSettings.Get("chanceStaticDecal").ToFloat();
			if (Math.RandomInt(0,101) < chanceStaticDecal)		
				animatedBloodManager.SpawnGenericSplatter(currentCharacter, hitTransform[0], hitTransform[1]);
			
				
		}
		
	}
	
	
	
	
	
	
	
	
	//------------------------------------------------------------------------------------------------


	
	
	
	override void CreateBleedingParticleEffect(notnull HitZone hitZone, float bleedingRate, int colliderDescriptorIndex)
	{
		// Play Bleeding particle
		if (m_sBleedingParticle.IsEmpty())
			return;
		
		RemoveBleedingParticleEffect(hitZone);
		
		if (bleedingRate == 0 || m_fBleedingParticleRateScale == 0)
			return;
		
		// TODO: Blood traces on ground that should be left regardless of clothing, perhaps just delayed
		SCR_CharacterHitZone characterHitZone = SCR_CharacterHitZone.Cast(hitZone);
		
		//Let's just disable this.
		//if (characterHitZone.IsCovered())
		//	return;
		
		// Get bone node
		vector transform[4];
		int boneIndex;
		int boneNode;
		if (!hitZone.TryGetColliderDescription(GetOwner(), colliderDescriptorIndex, transform, boneIndex, boneNode))
			return;
		
		SCR_ParticleEmitter particleEmitter = SCR_ParticleAPI.PlayOnObjectPTC(GetOwner(), m_sBleedingParticle, vector.Zero, vector.Zero, boneNode);
		SCR_ParticleAPI.LerpAllEmitters(particleEmitter, bleedingRate * m_fBleedingParticleRateScale, EmitterParam.BIRTH_RATE);
		
		if (!m_mBleedingParticles)
			m_mBleedingParticles = new map<HitZone, SCR_ParticleEmitter>;
		
		m_mBleedingParticles.Insert(hitZone, particleEmitter);
	}
	


	

}


class DecalWrapper
{
	Decal wrappedDecal;
	
	
	void DecalWrapper(Decal d)
	{
		wrappedDecal = d;
	
	}

}