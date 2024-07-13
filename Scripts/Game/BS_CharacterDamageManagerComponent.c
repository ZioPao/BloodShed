modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{

	ref map<string, string> bsSettings;
	const string BS_FileNameJson = "BS_Settings.json";
	const string BS_MOD_ID = "59D925199B6E6BFD";

	IEntity currentCharacter;
	bool alreadyDestroyed = false;
	float timerBetweenSplatters;
	World world;
	BS_AnimatedBloodManager animatedBloodManager;

	override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
		currentCharacter = owner;
		world = owner.GetWorld();

		////////////////////////////////////////////////////////////////////////////////
		// OrderedVariablesMap bsVariablesMap = new OrderedVariablesMap();

		// bsVariablesMap.Set("waitTimeBetweenFrames", new VariableInfo("Wait between frames", "0.033", EFilterType.TYPE_FLOAT));
		// bsVariablesMap.Set("enableWeaponSplatters", new VariableInfo("Enable Weapon Splatters (Currently kinda broken)", "0", EFilterType.TYPE_BOOL));
		// bsVariablesMap.Set("enableDamageDroplets", new VariableInfo("Enable Droplets from bleeding", "1", EFilterType.TYPE_BOOL));
		// bsVariablesMap.Set("enableBloodTrails", new VariableInfo("Enable blood trails when bleeding", "1", EFilterType.TYPE_BOOL));

		// bsVariablesMap.Set("bloodpoolMinimumAlphaMulChange", new VariableInfo("Alpha Mul Bloodpools - Min Random Change", "0.0002", EFilterType.TYPE_FLOAT));
		// bsVariablesMap.Set("bloodpoolMaximumAlphaMulChange", new VariableInfo("Alpha Mul Bloodpools - Max Random Change", "0.03", EFilterType.TYPE_FLOAT));

		// bsVariablesMap.Set("wallsplatterMinimumAlphaMulChange", new VariableInfo("Alpha Mul Wallsplatters - Min Random Change", "0.0001", EFilterType.TYPE_FLOAT));
		// bsVariablesMap.Set("wallsplatterMaximumAlphaMulChange", new VariableInfo("Alpha Mul Wallsplatters - Max Random Change", "0.02", EFilterType.TYPE_FLOAT));

		// bsVariablesMap.Set("wallsplatterMinimumAlphaTestChange", new VariableInfo("Alpha Test Wallsplatters - Min Random Change", "0.0001", EFilterType.TYPE_FLOAT));
		// bsVariablesMap.Set("wallsplatterMaximumAlphaTestChange", new VariableInfo("Alpha Test Wallsplatters - Max Random Change", "0.02", EFilterType.TYPE_FLOAT));

		// bsVariablesMap.Set("maxAlphaMul", new VariableInfo("Alpha Test Maximum value", "5", EFilterType.TYPE_FLOAT));			//max 5
		// bsVariablesMap.Set("minAlphaTest", new VariableInfo("Alpha Test Minimum value", "0.1", EFilterType.TYPE_FLOAT));

		// bsVariablesMap.Set("chanceStaticDecal", new VariableInfo("Chance of a static blood decal to appear (0 to 100)", "50", EFilterType.TYPE_FLOAT));

		// bsVariablesMap.Set("maxDecalsPerChar", new VariableInfo("Max Decals per Character", "2", EFilterType.TYPE_INT));
		// bsVariablesMap.Set("maxDecalsPlayerWeapon", new VariableInfo("Max Decals for Player Weapon", "4", EFilterType.TYPE_INT));

		// bsVariablesMap.Set("bloodpoolSize", new VariableInfo("Bloodpol Size", "1.5", EFilterType.TYPE_FLOAT));
		// bsVariablesMap.Set("wallsplatterSize", new VariableInfo("Wallsplatter Size", "1", EFilterType.TYPE_FLOAT));

		// if (!MCF_SettingsManager.GetJsonManager(BS_MOD_ID))
		//{
		//	MCF_SettingsManager.Setup(BS_MOD_ID, BS_FileNameJson, bsVariablesMap);

		//}
		// else if (!bsSettings)
		//{
		//	bsSettings = MCF_SettingsManager.GetModSettings(BS_MOD_ID);
		//	MCF_SettingsManager.GetJsonManager(BS_MOD_ID).SetUserHelpers(bsVariablesMap);
		//}

		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();
		if (!animatedBloodManager)
			animatedBloodManager = BS_AnimatedBloodManager.Cast(GetGame().SpawnEntity(BS_AnimatedBloodManager, GetGame().GetWorld(), null));
	}

	override void OnDamage(notnull BaseDamageContext damageContext)
	{
		super.OnDamage(damageContext);

		// EDamageType type,
		// float damage,
		// HitZone pHitZone,
		// IEntity instigator,
		// inout vector hitTransform[3],
		// float speed,
		// int colliderID,
		// int nodeID

		int colliderID = damageContext.colliderID;
		HitZone pHitZone = damageContext.struckHitZone;
		vector hitTransform[3];
		hitTransform[0] = damageContext.hitPosition;
		hitTransform[1] = damageContext.hitDirection;
		hitTransform[2] = damageContext.hitNormal;

		float damage = damageContext.damageValue;

		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();

		int correctNodeId;
		int colliderDescriptorIndex = pHitZone.GetColliderDescriptorIndex(colliderID);
		pHitZone.TryGetColliderDescription(currentCharacter, colliderDescriptorIndex, null, null, correctNodeId);

		int enableDamageDroplets = 1; // bsSettings.Get("enableDamageDroplets").ToInt();
		int enableBloodTrails = 1;	  // bsSettings.Get("enableBloodTrails").ToInt();

		if (IsDamagedOverTime(EDamageType.BLEEDING))
		{

			if (enableBloodTrails == 1)
			{
				Print("Spawning blood trails");
				GetGame().GetCallqueue().CallLater(animatedBloodManager.SpawnBloodTrail, 10, true, currentCharacter, hitTransform[0], damage);
			}

			if (enableDamageDroplets == 1)
			{
				// TODO
				Print("Spawning bleeding");
				SCR_CharacterHitZone tempHitZone = SCR_CharacterHitZone.Cast(pHitZone);
				float bleedingRate;
				if (tempHitZone)
					bleedingRate = (tempHitZone.GetMaxBleedingRate() * 100) + Math.RandomIntInclusive(-100, 100);
				else
					bleedingRate = 1500 + Math.RandomIntInclusive(-200, 200);

				GetGame().GetCallqueue().CallLater(animatedBloodManager.SpawnDroplets, bleedingRate, true, currentCharacter, hitTransform[0]);
			}
		}

		Print(hitTransform[0].Length());

		if (hitTransform[0].Length() != 0)
		{

			EDamageState currentState = GetState();

			Print("Current state: " + currentState);		// 3 is destroyed
			Print("char is already destr? " + alreadyDestroyed);

			// todo not 100% certain that this is gonna be "Destroyed" when the char is dying.
			if (currentState == EDamageState.STATE3 || currentState == EDamageState.STATE3 && !alreadyDestroyed)
			{

				GetGame().GetCallqueue().CallLater(animatedBloodManager.SpawnGroundBloodpool, 2000, false, currentCharacter, hitTransform[0], hitTransform[1], correctNodeId);
				alreadyDestroyed = true; // only once
			}
			else if (damage > 20.0)
			{
				animatedBloodManager.SpawnWallSplatter(currentCharacter, hitTransform[0], hitTransform[1]);
			}

			// bsSettings = MCF_SettingsManager.GetModSettings(BS_MOD_ID);
			// int enableWeaponSplatters = bsSettings.Get("enableWeaponSplatters").ToInt();

			int enableWeaponSplatters = 0;

			if (enableWeaponSplatters == 1)
				animatedBloodManager.GenerateWeaponSplatters(currentCharacter);

			float chanceStaticDecal = 50; // bsSettings.Get("chanceStaticDecal").ToFloat();
			if (Math.RandomInt(0, 101) < chanceStaticDecal)
				animatedBloodManager.SpawnGenericSplatter(currentCharacter, hitTransform[0], hitTransform[1]);
		}
	}

	//------------------------------------------------------------------------------------------------

	override void CreateBleedingParticleEffect(notnull HitZone hitZone, int colliderDescriptorIndex)
	{
		// Play Bleeding particle
		if (m_sBleedingParticle.IsEmpty())
			return;

		RemoveBleedingParticleEffect(hitZone);

		//if (bleedingRate == 0 || m_fBleedingParticleRateScale == 0)
		//	return;

		// TODO: Blood traces on ground that should be left regardless of clothing, perhaps just delayed
		SCR_CharacterHitZone characterHitZone = SCR_CharacterHitZone.Cast(hitZone);

		// Let's just disable this.
		// if (characterHitZone.IsCovered())
		//	return;

		// Get bone node
		vector transform[4];
		int boneIndex;
		int boneNode;
		if (!hitZone.TryGetColliderDescription(GetOwner(), colliderDescriptorIndex, transform, boneIndex, boneNode))
			return;

		// TODO Re-enable once we figure out what we have to do with this ParticleEmitter stuff
		// SCR_ParticleEmitter particleEmitter = SCR_ParticleAPI.PlayOnObjectPTC(GetOwner(), m_sBleedingParticle, vector.Zero, vector.Zero, boneNode);
		// SCR_ParticleAPI.LerpAllEmitters(particleEmitter, bleedingRate * m_fBleedingParticleRateScale, EmitterParam.BIRTH_RATE);

		// if (!m_mBleedingParticles)
		//	m_mBleedingParticles = new map<HitZone, SCR_ParticleEmitter>;

		// m_mBleedingParticles.Insert(hitZone, particleEmitter);
	}

	override void RemoveBleedingFromArray(notnull HitZone hitZone)
	{
		super.RemoveBleedingFromArray(hitZone);

		// DisableBloodTrail();

		animatedBloodManager = BS_AnimatedBloodManager.GetInstance();
		GetGame().GetCallqueue().Remove(animatedBloodManager.SpawnDroplets);
		GetGame().GetCallqueue().Remove(animatedBloodManager.SpawnBloodTrail);
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