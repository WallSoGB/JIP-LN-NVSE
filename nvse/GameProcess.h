#pragma once

struct PackageInfo
{
	TESPackage		*package;		// 00
	union
	{
		TESPackageData		*packageData;	// 04
		ActorPackageData	*actorPkgData;
	};
	TESObjectREFR	*targetRef;		// 08
	UInt32			unk0C;			// 0C	Initialized to 0FFFFFFFFh, set to 0 on start
	float			unk10;			// 10	Initialized to -1.0	. Set to GameHour on start so some time
	UInt32			flags;			// 14	Flags, bit0 would be not created and initialized
};

// 64
struct ActorHitData
{
	enum HitFlags
	{
		kFlag_TargetIsBlocking =		1,
		kFlag_TargetWeaponOut =			2,
		kFlag_IsCritical =				4,
		kFlag_OnDeathCritEffect =		8,
		kFlag_IsFatal =					0x10,
		kFlag_DismemberLimb =			0x20,
		kFlag_ExplodeLimb =				0x40,
		kFlag_CrippleLimb =				0x80,
		kFlag_BreakWeaponNonEmbedded =	0x100,
		kFlag_BreakWeaponEmbedded =		0x200,
		kFlag_IsSneakAttack =			0x400,
		kFlag_ArmorPenetrated =			0x80000000	// JIP only
	};

	Actor				*source;		// 00
	Actor				*target;		// 04
	union								// 08
	{
		Projectile		*projectile;
		Explosion		*explosion;
	};
	UInt32				weaponAV;		// 0C
	SInt32				hitLocation;	// 10
	float				healthDmg;		// 14
	float				wpnBaseDmg;		// 18	Skill and weapon condition modifiers included
	float				fatigueDmg;		// 1C
	float				limbDmg;		// 20
	float				blockDTMod;		// 24
	float				armorDmg;		// 28
	float				flt2C;			// 2C
	TESObjectWEAP		*weapon;		// 30
	float				healthPerc;		// 34
	NiVector3			impactPos;		// 38
	NiVector3			impactAngle;	// 44
	UInt32				unk50;			// 50
	void				*ptr54;			// 54
	UInt32				flags;			// 58
	float				dmgMult;		// 5C
	SInt32				unk60;			// 60	Unused; rigged by CopyHitDataHook to store hitLocation
};

struct ProjectileData;

// 30
class BaseProcess
{
public:
	struct Data2C
	{
		enum
		{
			kCached_Radius =				0x1,
			kCached_WidthX =				0x2,
			kCached_WidthY =				0x4,
			kCached_DPS =					0x8,
			kCached_MedicineSkillMult =		0x10,
			kCached_Paralysis =				0x20,
			kCached_HealRate =				0x40,
			kCached_FatigueReturnRate =		0x80,
			kCached_PerceptionCondition =	0x100,
			kCached_EyeHeight =				0x200,
			kCached_SomethingShouldAttack =	0x400,
			kCached_WalkSpeed =				0x1000,
			kCached_RunSpeed =				0x2000,
			kCached_NoCrippledLegs =		0x4000,
			kCached_Height =				0x8000,
			kCached_IsGhost =				0x10000000,
			kCached_Health =				0x20000000,
			kCached_Fatigue =				0x40000000,
			kCached_SurvivalSkillMult =		0x80000000
		};

		float	radius;					// 00
		float	widthX;					// 04
		float	widthY;					// 08
		float	height;					// 0C
		float	DPS;					// 10
		float	medicineSkillMult;		// 14
		float	survivalSkillMult;		// 18
		float	paralysis;				// 1C
		float	healRate;				// 20
		float	fatigueReturnRate;		// 24
		float	perceptionCondition;	// 28
		float	eyeHeight;				// 2C
		SInt32	unk30;					// 30
		SInt32	unk34;					// 34
		float	walkSpeed;				// 38
		float	runSpeed;				// 3C
		UInt8	hasNoCrippledLegs;		// 40
		UInt8	pad41[3];				// 41
		UInt32	flags;					// 44
	};

	virtual void	Destroy(bool deFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	Unk_16(void);
	virtual void	Unk_17(void);
	virtual void	Unk_18(void);
	virtual void	Unk_19(void);
	virtual void	Unk_1A(void);
	virtual void	Unk_1B(void);
	virtual void	Unk_1C(void);
	virtual void	Unk_1D(void);
	virtual void	Unk_1E(void);
	virtual void	Unk_1F(void);
	virtual void	Unk_20(void);
	virtual void	Unk_21(void);
	virtual void	Unk_22(void);
	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);
	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual DetectionEvent	*GetDetectionEvent(Actor *actor);	// arg not used
	virtual void	CreateDetectionEvent(Actor *actor, float posX, float posY, float posZ, UInt32 soundLevel, UInt32 eventType, TESObjectREFR *locationRef);	// actor & eventType unused
	virtual void	RemoveDetectionEvent();
	virtual void	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(void);
	virtual bool	GetHasCaughtPlayerPickpocketting();
	virtual void	SetHasCaughtPlayerPickpocketting(bool doSet);
	virtual void	Unk_46(void);
	virtual void	Unk_47(void);
	virtual void	Unk_48(void);
	virtual void	Unk_49(void);
	virtual TESForm *GetLowProcess40();
	virtual void	Unk_4B(void);
	virtual void	Unk_4C(void);
	virtual void	Unk_4D(void);
	virtual void	Unk_4E(void);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	Unk_51(void);
	virtual ExtraContainerChanges::EntryData *GetWeaponInfo();
	virtual ExtraContainerChanges::EntryData *GetAmmoInfo();
	virtual void	Unk_54(void);
	virtual void	Unk_55(void);
	virtual void	Unk_56(void);
	virtual void	Unk_57(void);
	virtual void	Unk_58(void);
	virtual void	Unk_59(void);
	virtual void	SetAmmoInfo(ExtraContainerChanges::EntryData *_ammoInfo);
	virtual void	Unk_5B(void);
	virtual void	HandleQueuedEquipItems(Actor *actor);
	virtual void	Unk_5D(void);	// Called by 5E with count itemExtraList item
	virtual void	QueueEquipItem(Actor *actor, bool doEquip, TESForm *item, UInt32 count, ExtraDataList *xDataList, bool applyEnchantment, bool noUnequip, UInt8 arg8, UInt8 arg9, bool playSound);
	virtual void	Unk_5F(void);
	virtual void	Unk_60(void);
	virtual NiNode	*GetProjectileNode();
	virtual void	SetProjectileNode(NiNode *node);
	virtual void	Unk_63(void);
	virtual NiNode	*GetWeaponNode(ValidBip01Names *vbp01Names);
	virtual void	Unk_65(void);
	virtual void	Unk_66(void);
	virtual void	Unk_67(void);
	virtual NiNode	*GetWeaponNode2(UInt32 arg);
	virtual void	Unk_69(void);
	virtual bool	IsUsingOneHandGrenade();
	virtual bool	IsUsingOneHandMine();
	virtual bool	IsUsingOneHandThrownMineOrGrenade();
	virtual bool	IsUsingOneHandThrown();
	virtual AnimData	*GetAnimData();
	virtual void	Unk_6F(void);
	virtual void	Unk_70(void);
	virtual void	Unk_71(void);
	virtual void	Unk_72(void);
	virtual void	Unk_73(bool weaponOut, ValidBip01Names *validBip01Names, AnimData *pAnimData, Actor *actor);
	virtual void	Unk_74(void);
	virtual void	Unk_75(void);
	virtual void	Unk_76(Actor *actor);
	virtual void	Unk_77(void);
	virtual void	Unk_78(void);
	virtual void	Unk_79(void);
	virtual void	Unk_7A(void);
	virtual void	Unk_7B(void);
	virtual void	Unk_7C(void);
	virtual void	Unk_7D(void);
	virtual void	Unk_7E(void);
	virtual void	Unk_7F(void);
	virtual void	Unk_80(void);
	virtual void	Unk_81(void);
	virtual void	Unk_82(void);
	virtual TESPackage	*GetInterruptPackage();
	virtual void	SetInterruptPackage(TESPackage *package, Actor *onActor);
	virtual void	StopInterruptPackage();
	virtual void	Unk_86(void);	// 086 - SetInterruptPackageTargetRef
	virtual void	Unk_87(void);	// 087 - SetInterruptPackageTargetRef
	virtual void	Unk_88(void);	// 088 - IncreaseInterruptPackageUnk00C
	virtual void	Unk_89(void);
	virtual void	Unk_8A(void);
	virtual TESPackage	*GetStablePackage();
	virtual void	SetStablePackage(TESPackage *package, Actor *onActor);
	virtual void	StopStablePackage();
	virtual void	Unk_8E(void);
	virtual void	Unk_8F(void);
	virtual void	Unk_90(void);
	virtual void	Unk_91(void);
	virtual void	Unk_92(void);	// Only HighProcess, get Unk0454
	virtual void	Unk_93(void);
	virtual void	Unk_94(void);
	virtual void	Unk_95(void);
	virtual void	Unk_96(void);
	virtual void	Unk_97(void);
	virtual void	Unk_98(void);
	virtual void	Unk_99(void);
	virtual void	Unk_9A(void);
	virtual void	Unk_9B(void);
	virtual void	Unk_9C(void);
	virtual TESPackageData	*GetPackageData();
	virtual void	Unk_9E(void);
	virtual TESPackage	*GetCurrentPackage();
	virtual UInt32	GetPackageInfo0C();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual bhkCharacterController	*GetCharacterController();
	virtual void	SetCharacterController(bhkCharacterController *charCtrl);
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual void	Unk_AA();
	virtual void	Unk_AB();
	virtual void	Unk_AC();
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3();
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();
	virtual void	Unk_B8();
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	SetDiveBreath(float breath);
	virtual float	GetDiveBreath();
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	Unk_C4();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual bool	GetAlerted();
	virtual void	SetAlert(bool alert);
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual UInt8	GetPlantedExplosive();
	virtual TESIdleForm	*GetLastPlayedIdle();
	virtual void	SetLastPlayedIdle(TESIdleForm *idleForm);
	virtual void	StopIdle();
	virtual void	Unk_E6();
	virtual void	Unk_E7();	// float GetActorValue
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	Unk_EB();
	virtual void	Unk_EC();
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual SInt16	GetCurrentAction();
	virtual BSAnimGroupSequence	*GetCurrentSequence();
	virtual void	SetCurrentActionAndSequence(SInt16 action, BSAnimGroupSequence *sequence);
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual bool	IsReadyForAnim();
	virtual void	Unk_FF();
	virtual void	SetIsAiming(bool aiming);
	virtual bool	GetIsAiming();
	virtual void	Unk_102();
	virtual SInt32	GetKnockedState();
	virtual void	SetKnockedState(char state);
	virtual void	Unk_105();
	virtual void	PushActorAway(Actor *pushed, float posX, float posY, float posZ, float force);
	virtual void	Unk_107(Actor *actor);
	virtual void	Unk_108();
	virtual void	SetNthAnimSequenceWeight(UInt32 index, BSAnimGroupSequence *animSeq);
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual bool	IsWeaponOut();
	virtual void	SetWeaponOut(Actor *actor, bool weaponOut);
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119(Actor *actor);
	virtual void	Unk_11A(UInt32 unk);
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual bool	Unk_11D(UInt32 arg);
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual bool	IsOnDialoguePackage(Actor *actor);
	virtual UInt32	GetSitSleepState();
	virtual void	Unk_130();
	virtual void	Unk_131();
	virtual TESObjectREFR	*GetCurrentFurnitureRef();
	virtual void	Unk_133();
	virtual void	Unk_134();
	virtual void	Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual void	Unk_13B();
	virtual void	Unk_13C();
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F(UInt32 unk);
	virtual void	Unk_140();
	virtual DetectionData *GetDetectionData(Actor *target, UInt32 detecting);
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Unk_145();
	virtual void	Unk_146();
	virtual void	Unk_147();
	virtual void	Unk_148();
	virtual void	Unk_149();
	virtual void	Unk_14A();
	virtual void	Unk_14B();
	virtual void	Unk_14C();
	virtual void	Unk_14D();
	virtual void	Unk_14E();
	virtual void	Unk_14F();
	virtual void	Unk_150();
	virtual void	Unk_151();
	virtual void	Unk_152();
	virtual void	Unk_153();
	virtual void	Unk_154();
	virtual void	Unk_155();
	virtual void	Unk_156();
	virtual void	Unk_157();
	virtual void	Unk_158();
	virtual void	Unk_159();
	virtual void	Unk_15A();
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Unk_160();
	virtual void	Unk_161();
	virtual void	Unk_162();
	virtual void	Unk_163();
	virtual void	Unk_164();
	virtual void	Unk_165();
	virtual void	Unk_166();
	virtual void	Unk_167();
	virtual void	Unk_168();
	virtual void	Unk_169();
	virtual void	Unk_16A();
	virtual float	GetActorAlpha();
	virtual void	SetActorAlpha(float alpha);
	virtual void	Unk_16D();
	virtual void	Unk_16E();
	virtual void	Unk_16F();
	virtual void	Unk_170();
	virtual void	Unk_171();
	virtual void	Unk_172();
	virtual void	Unk_173();
	virtual void	Unk_174();
	virtual void	Unk_175();
	virtual void	Unk_176();
	virtual void	Unk_177();
	virtual void	Unk_178();
	virtual void	Unk_179();
	virtual void	Unk_17A();
	virtual void	Unk_17B();
	virtual BSBound	*GetBoundingBox();
	virtual void	SetBoundingBox(BSBound *bounds);
	virtual void	Unk_17E();
	virtual void	Unk_17F();
	virtual void	Unk_180();
	virtual void	Unk_181();
	virtual void	Unk_182();
	virtual void	Unk_183();
	virtual void	Unk_184();
	virtual void	SetQueuedIdleFlags(UInt32 flags);
	virtual UInt32	GetQueuedIdleFlags();
	virtual void	Unk_187();
	virtual void	Unk_188();
	virtual void	Unk_189();
	virtual void	Unk_18A(Actor *actor);
	virtual void	Unk_18B();
	virtual void	Unk_18C();
	virtual void	Unk_18D();
	virtual void	Unk_18E();
	virtual void	Unk_18F();
	virtual void	Unk_190();
	virtual void	Unk_191();
	virtual void	Unk_192(UInt8 unk);
	virtual void	Unk_193();
	virtual void	Unk_194();
	virtual void	Unk_195();
	virtual void	Unk_196();
	virtual void	Unk_197();
	virtual void	Unk_198();
	virtual void	Unk_199();
	virtual void	Unk_19A();
	virtual void	Unk_19B();
	virtual void	Unk_19C();
	virtual void	Unk_19D();
	virtual void	Unk_19E();
	virtual void	Unk_19F();
	virtual void	Unk_1A0();
	virtual void	Unk_1A1();
	virtual void	Unk_1A2();
	virtual void	Unk_1A3();
	virtual void	Unk_1A4();
	virtual void	Unk_1A5();
	virtual void	Unk_1A6();
	virtual void	Unk_1A7();
	virtual void	Unk_1A8();
	virtual void	Unk_1A9();
	virtual void	Unk_1AA();
	virtual void	Unk_1AB();
	virtual void	Unk_1AC();
	virtual void	Unk_1AD();
	virtual ProjectileData	*GetProjectileData();
	virtual void	Unk_1AF();
	virtual void	Unk_1B0();
	virtual void	Unk_1B1();
	virtual void	Unk_1B2();
	virtual void	Unk_1B3();
	virtual void	Unk_1B4();
	virtual void	Unk_1B5();
	virtual void	Unk_1B6();
	virtual void	Unk_1B7();
	virtual void	Unk_1B8();
	virtual void	Unk_1B9();
	virtual void	Unk_1BA();
	virtual void	Unk_1BB();
	virtual void	Unk_1BC();
	virtual void	Unk_1BD();
	virtual void	Unk_1BE();
	virtual void	Unk_1BF();
	virtual void	Unk_1C0();
	virtual void	Unk_1C1();
	virtual void	Unk_1C2();
	virtual void	Unk_1C3();
	virtual void	Unk_1C4();
	virtual void	Unk_1C5();
	virtual TESIdleForm	*GetIdleForm350();
	virtual void	SetIdleForm350(TESIdleForm *idleForm);
	virtual void	Unk_1C8();
	virtual void	Unk_1C9();
	virtual void	Unk_1CA();
	virtual void	Unk_1CB();
	virtual void	Unk_1CC();
	virtual float	GetLightAmount();
	virtual void	SetLightAmount(float lightAmount);
	virtual void	Unk_1CF();
	virtual void	Unk_1D0();
	virtual void	Unk_1D1();
	virtual void	Unk_1D2();
	virtual void	Unk_1D3();
	virtual void	Unk_1D4();
	virtual void	Unk_1D5();
	virtual void	Unk_1D6();
	virtual void	Unk_1D7();
	virtual void	SetWaterRadsSec(float radsSec);
	virtual float	GetWaterRadsSec();
	virtual void	Unk_1DA();
	virtual float	GetRadsSec();
	virtual ActorHitData *GetHitData();
	virtual void	CopyHitData(ActorHitData *hitData);
	virtual void	ResetHitData();
	virtual ActorHitData *GetHitData254();
	virtual void	CopyHitData254(ActorHitData *hitData);
	virtual void	ResetHitData254();
	virtual void	Unk_1E2();
	virtual void	Unk_1E3();
	virtual void	Unk_1E4();
	virtual void	Unk_1E5();
	virtual void	Unk_1E6();
	virtual void	Unk_1E7();
	virtual void	Unk_1E8();
	virtual void	Unk_1E9();
	virtual void	Unk_1EA();
	virtual void	Unk_1EB();
	virtual void	Unk_1EC();
	virtual void	Unk_1ED();	// Leads to Last Target

	PackageInfo		currentPackage;	// 04
	float			unk1C;			// 1C	not initialized, only by descendant!
	float			unk20;			// 20	not initialized, only by descendant to -1.0! flt020 gets set to GameHour minus one on package evaluation
	UInt32			unk24;			// 24	not initialized, only by descendant!
	UInt32			processLevel;	// 28	not initialized, only by descendant to 3 for Low, 2 for MidlleLow, 1 MiddleHighProcess and 0 for HigProcess
	Data2C			*unk2C;			// 2C
};

// B4
class LowProcess : public BaseProcess
{
public:
	struct FloatPair
	{
		float	flt000;
		float	flt004;
	};

	struct ActorValueModifier
	{
		UInt8	actorValue;	// 00 Might allow for other values
		UInt8	pad[3];		// 01
		float	damage;		// 04
	};

	struct ActorValueModifiers
	{
		tList<ActorValueModifier>	avModifierList;	// 00
		UInt8						unk008;			// 08
		UInt8						pad009[3];		// 09
		void						**modifiedAV;	// 0C	array of damaged actorValue
	};	// 10

	virtual void	Unk_1EE();
	virtual void	Unk_1EF();
	virtual void	Unk_1F0();
	virtual void	Unk_1F1();
	virtual void	Unk_1F2();
	virtual void	Unk_1F3();
	virtual void	Unk_1F4();
	virtual void	Unk_1F5();
	virtual void	Unk_1F6();
	virtual void	Unk_1F7();
	virtual void	Unk_1F8();
	virtual void	Unk_1F9();
	virtual void	Unk_1FA();
	virtual void	Unk_1FB();
	virtual void	Unk_1FC();
	virtual void	Unk_1FD();
	virtual void	Unk_1FE();
	virtual void	Unk_1FF();
	virtual void	Unk_200();
	virtual void	Unk_201();
	virtual void	Unk_202();
	virtual void	Unk_203();
	virtual void	Unk_204();
	virtual void	Unk_205();
	virtual void	Unk_206();

	UInt8				byte30;		// 8 = IsAlerted
	UInt8				pad31[3];
	UInt32				unk34;
	FloatPair			unk38;
	TESForm				*unk40;		// Used when picking idle anims.
	UInt32				unk44;		// not initialized!	refr, expected actor, might be CombatTarget
	UInt32				unk48;
	UInt32				unk4C;
	UInt32				unk50;
	UInt32				unk54;		// not initialized!
	UInt32				unk58;
	UInt32				unk5C;
	tList<UInt32>		unk60;		// List
	UInt32				unk68;
	UInt32				unk6C;
	tList<TESForm>		unk70;
	tList<UInt32>		unk78;
	tList<UInt32>		unk80;
	UInt32				unk88;
	UInt32				unk8C;
	UInt32				unk90;
	UInt32				unk94;
	ActorValueModifiers	damageModifiers;
	float				gameDayDied;
	UInt32				unkAC;		// not initialized!
	UInt32				unkB0;		// not initialized!
};

// C8
class MiddleLowProcess : public LowProcess
{
public:
	virtual void		Unk_207();

	UInt32				unk0B4;			// B4
	ActorValueModifiers	tempModifiers;	// B8
};

// 04
class AnimSequenceBase
{
public:
	virtual void	Destroy(bool deFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
};

// 08
class AnimSequenceSingle : public AnimSequenceBase
{
public:
	UInt32		unk04;		// 04
};

// 08
class AnimSequenceMultiple : public AnimSequenceBase
{
public:
	struct Struct04
	{
		UInt32		unk00;
		UInt32		unk04;
		UInt32		unk08;
	};

	Struct04	*ptr04;		// 04
};

enum AnimAction
{
	kAnimAction_None = -1,
	kAnimAction_Equip_Weapon = 0,
	kAnimAction_Unequip_Weapon,
	kAnimAction_Attack,
	kAnimAction_Attack_Eject,
	kAnimAction_Attack_Follow_Through,
	kAnimAction_Attack_Throw,
	kAnimAction_Attack_Throw_Attach,
	kAnimAction_Block,
	kAnimAction_Recoil,
	kAnimAction_Reload,
	kAnimAction_Stagger,
	kAnimAction_Dodge,
	kAnimAction_Wait_For_Lower_Body_Anim,
	kAnimAction_Wait_For_Special_Idle,
	kAnimAction_Force_Script_Anim,
	kAnimAction_ReloadLoopStart,
	kAnimAction_ReloadLoopEnd,
	kAnimAction_ReloadLoop
};

// 100+
struct AnimData
{
	struct Unk124
	{
		struct Unk18
		{
			UInt32			unk00[9];
			UInt32			unk24;
		};

		UInt32			unk00;
		UInt32			unk04;
		UInt32			unk08;
		UInt32			unk0C;
		UInt32			unk10;
		UInt32			unk14;
		Unk18			*unk18;
	};

	struct Unk128
	{
		UInt32			unk00[11];
		TESIdleForm		*idle2C;
	};

	UInt32							unk000;				// 000
	Actor							*actor;				// 004
	NiNode							*nSceneRoot;		// 008
	NiNode							*nBip01;			// 00C
	UInt32							unk010;				// 010
	float							flt014;				// 014
	float							flt018;				// 018
	UInt32							unk01C;				// 01C
	float							flt020;				// 020
	UInt32							unk024;				// 024
	NiNode							*nPelvis;			// 028
	NiNode							*nBip01Copy;		// 02C
	NiNode							*nLForearm;			// 030
	NiNode							*nHead;				// 034
	NiNode							*nWeapon;			// 038
	UInt32							unk03C[2];			// 03C
	NiNode							*nNeck1;			// 044
	UInt32							unk048;				// 048
	UInt16							animGroupIDs[8];	// 04C
	SInt32							sequenceState1[8];	// 05C
	SInt32							sequenceState2[8];	// 07C
	UInt16							word09C[8];			// 09C
	UInt32							unk0AC[8];			// 0AC
	float							flt0CC;				// 0CC
	float							flt0D0;				// 0D0
	UInt32							unk0D4;				// 0D4
	NiControllerManager				*unk0D8;			// 0D8
	NiTPointerMap<AnimSequenceBase>	*unk0DC;			// 0DC
	BSAnimGroupSequence				*animSequence[8];	// 0E0
	BSAnimGroupSequence				*animSeq100;		// 100
	UInt32							unk104;				// 104
	UInt32							unk108;				// 108
	float							flt10C;				// 10C
	float							flt110;				// 110
	float							flt114;				// 114
	float							flt118;				// 118
	float							flt11C;				// 11C
	UInt8							byte120;			// 120
	UInt8							byte121;			// 121
	UInt16							word122;			// 122
	Unk124							*unk124;			// 124
	Unk128							*unk128;			// 128
};
STATIC_ASSERT(sizeof(AnimData) == 0x12C);

class QueuedFile;
class BSFaceGenAnimationData;

// 25C
class MiddleHighProcess : public MiddleLowProcess
{
public:
	virtual void	SetAnimation(UInt32 newAnimation);
	virtual void	Unk_209();
	virtual void	Unk_20A();
	virtual void	Unk_20B();
	virtual void	Unk_20C();
	virtual void	Unk_20D();
	virtual void	Unk_20E();
	virtual void	Unk_20F();
	virtual void	Unk_210();
	virtual void	Unk_211();
	virtual void	Unk_212();
	virtual void	Unk_213();
	virtual void	Unk_214();
	virtual void	Unk_215();
	virtual void	Unk_216();
	virtual void	Unk_217();
	virtual void	Unk_218();
	virtual void	Unk_219();
	virtual void	Unk_21A();
	virtual void	Unk_21B();

	enum KnockedState
	{
		kState_None,
		kState_KnockedDown,
		kState_Ragdolled,
		kState_Unconscious,
		kState_Unknown4,
		kState_Unknown5,
		kState_GettingUp
	};

	tList<TESForm>						unk0C8;				// 0C8
	tList<UInt32>						unk0D0;				// 0D0
	UInt32								unk0D8[3];			// 0D8
	PackageInfo							interruptPackage;	// 0E4
	UInt8								unk0FC[12];			// 0FC	Saved as one, might be Pos/Rot given size
	UInt32								unk108;				// 108
	TESIdleForm							*LastPlayedIdle;	// 10C
	UInt32								unk110;				// 110  EntryData, also handled as part of weapon code. AmmoInfo.
	ExtraContainerChanges::EntryData	*weaponInfo;		// 114
	ExtraContainerChanges::EntryData	*ammoInfo;			// 118
	QueuedFile							*unk11C;			// 11C
	UInt8								byt120;				// 120
	UInt8								byt121;				// 121
	UInt8								byt122;				// 122
	UInt8								fil123;				// 123
	UInt8								usingOneHandGrenade;// 124
	UInt8								usingOneHandMine;	// 125
	UInt8								usingOneHandThrown;	// 126
	UInt8								byte127;			// 127
	UInt32								unk128;				// 128 Gets copied over during TESNPC.CopyFromBase
	NiNode								*weaponNode;		// 12C
	NiNode								*projectileNode;	// 130
	UInt8								byt134;				// 134
	bool								isWeaponOut;		// 135
	UInt8								byt136;				// 136
	UInt8								byt137;				// 137
	bhkCharacterController				*charCtrl;			// 138
	UInt8								knockedState;		// 13C
	UInt8								sitSleepState;		// 13D
	UInt8								unk13E[2];			// 13E
	TESObjectREFR						*usedFurniture;		// 140
	UInt8								byte144;			// 144
	UInt8								unk145[3];			// 145
	UInt32								unk148[6];			// 148
	MagicItem							*magicItem160;		// 160
	UInt32								unk164[3];			// 164
	float								actorAlpha;			// 170
	UInt32								unk174;				// 174
	BSFaceGenAnimationData				*unk178;			// 178
	UInt8								byte17C;			// 17C
	UInt8								byte17D;			// 17D
	UInt8								byte17E;			// 17E
	UInt8								byte17F;			// 17F
	UInt32								unk180;				// 180
	UInt32								unk184;				// 184
	UInt8								hasCaughtPCPickpocketting;	// 188
	UInt8								byte189;			// 189
	UInt8								byte18A;			// 18A
	UInt8								byte18B;			// 18B
	UInt8								byte18C;			// 18C
	UInt8								byte18D[3];			// 18D
	UInt32								unk190[4];			// 190
	void								*ptr1A0;			// 1A0
	UInt32								unk1A4[2];			// 1A4
	tList<void>							*list1AC;			// 1AC
	tList<void>							list1B0;			// 1B0
	tList<void>							*list1B8;			// 1B8
	MagicTarget							*magicTarget1BC;	// 1BC
	AnimData							*animData;			// 1C0
	BSAnimGroupSequence					*animSequence[3];	// 1C4
	UInt32								unk1D0[3];			// 1D0
	NiNode								*limbNodes[15];		// 1DC
	NiNode								*unk218;			// 218
	NiNode								*unk21C;			// 21C
	BSShaderProperty					*shaderProp220;		// 220
	BSBound								*boundingBox;		// 224
	bool								isAiming;			// 228
	UInt8								pad229[3];			// 229
	UInt32								unk22C[2];			// 22C
	float								radsSec234;			// 234
	float								rads238;			// 238
	float								waterRadsSec;		// 23C
	ActorHitData						*hitData240;		// 240
	UInt32								unk244;				// 244
	BSFaceGenNiNode						*unk248;			// 248
	BSFaceGenNiNode						*unk24C;			// 24C
	NiTriShape							*unk250;			// 250
	ActorHitData						*hitData254;		// 254
	UInt32								unk258;				// 258
};
STATIC_ASSERT(sizeof(MiddleHighProcess) == 0x25C);