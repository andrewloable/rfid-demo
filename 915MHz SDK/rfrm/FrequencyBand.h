#pragma once

#define SELECTOR_ADDRESS 0x0C01
#define CONFIG_ADDRESS   0x0C02
#define MULTDIV_ADDRESS  0x0C03
#define PLLCC_ADDRESS    0x0C04

enum 
{
	DISABLED    = 0,
	ENABLED     = 1,
	UNKNOWN     = 2
};
typedef INT32U  BandState;

#define ClockKHz 24000.0

class CRFIDRadio;
class CFrequencyBand : public CObject
{
public:
	// Construction
	CFrequencyBand();
	CFrequencyBand(INT32U band);
	CFrequencyBand(INT32U    band,
		BandState state,
		INT16U    multiplier,
		INT16U    divider,
		INT16U    minDACBand,
		INT16U    affinityBand,
		INT16U    maxDACBand,
		INT16U    guardBand);
	CFrequencyBand(CFrequencyBand* frequencyBand);
	// Destruction
	virtual ~CFrequencyBand(void);
	void Serialize(CArchive& ar);

protected:
	DECLARE_SERIAL(CFrequencyBand)


protected:
	// Frequency members
	INT32U m_nBand;
	BandState m_enumState;
	INT16U m_nMultiplier;
	INT16U m_nDivider;
	INT16U m_nMinDACBand;
	INT16U m_nAffinityBand;
	INT16U m_nMaxDACBand;
	INT16U m_nGuardBand;

public:
	// Frequency Load/Store Function
	RFID_STATUS Load(CRFIDRadio* pRadio);
	RFID_STATUS Store(CRFIDRadio* pRadio);

	// Interface functions
	inline INT32U GetBand() { return m_nBand; }
	inline void SetBand(INT32U band) { m_nBand = band; }
	inline BOOL GetBandState() { return (BOOL)m_enumState; }
	inline void SetBandState(BOOL state) { m_enumState = (BandState)state; }
	inline INT16U GetMultiplier() {return m_nMultiplier;}
	inline void SetMultiplier(INT16U multiplier) {m_nMultiplier = multiplier;}
	inline INT16U GetDivider() {return m_nDivider;}
	inline void SetDivider(INT16U divider) {m_nDivider = divider;}
	inline INT16U GetMinDACBand() {return m_nMinDACBand;}
	inline void SetMinDACBand(INT16U minDACBand) {m_nMinDACBand = minDACBand;}
	inline INT16U GetAffinityBand() {return m_nAffinityBand;}
	inline void SetAffinityBand(INT16U affinityBand ) {m_nAffinityBand = affinityBand;}
	inline INT16U GetMaxDACBand() {return m_nMaxDACBand;}
	inline void SetMaxDACBand(INT16U maxDACBand) {m_nMaxDACBand = maxDACBand;}
	inline INT16U GetGuardBand() {return m_nGuardBand;}
	inline void SetGuardBand(INT16U guardBand) {m_nGuardBand = guardBand;}

	double Frequency();
};

