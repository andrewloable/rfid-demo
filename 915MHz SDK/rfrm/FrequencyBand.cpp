#include "StdAfx.h"
#include "FrequencyBand.h"
#include "RFIDRadio.h"

IMPLEMENT_SERIAL(CFrequencyBand, CObject, 0)  

void CFrequencyBand::Serialize(CArchive& ar)
{
	CObject::Serialize( ar );
// 	if( ar.IsStoring() )
// 		ar << i;
// 	else
// 		ar >> i;
}

CFrequencyBand::CFrequencyBand()
: m_nBand(0)
, m_enumState(DISABLED)
, m_nMultiplier(0)
, m_nDivider(0)
, m_nMinDACBand(0)
, m_nAffinityBand(0)
, m_nMaxDACBand(0)
, m_nGuardBand(0)
{
}

CFrequencyBand::CFrequencyBand(INT32U band)
: m_nBand(band)
, m_enumState(0)
, m_nMultiplier(0)
, m_nDivider(1)
, m_nMinDACBand(0)
, m_nAffinityBand(0)
, m_nMaxDACBand(0)
, m_nGuardBand(0)
{
}

CFrequencyBand::CFrequencyBand(INT32U    band,
			   BandState state,
			   INT16U    multiplier,
			   INT16U    divider,
			   INT16U    minDACBand,
			   INT16U    affinityBand,
			   INT16U    maxDACBand,
			   INT16U    guardBand)
			   : m_nBand(band)
			   , m_enumState(state)
			   , m_nMultiplier(multiplier)
			   , m_nDivider(divider)
			   , m_nMinDACBand(minDACBand)
			   , m_nAffinityBand(affinityBand)
			   , m_nMaxDACBand(maxDACBand)
			   , m_nGuardBand(guardBand)
{
}

CFrequencyBand::CFrequencyBand(CFrequencyBand* frequencyBand)
{
	memcpy(this, frequencyBand, sizeof(CFrequencyBand));
}


CFrequencyBand::~CFrequencyBand(void)
{
}

RFID_STATUS CFrequencyBand::Load(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	INT32U config            = 0;
	INT32U multdiv           = 0;
	INT32U pllcc             = 0;

	if(RFID_STATUS_OK !=
		(result = pRadio->SetConfigurationParameter( 
		SELECTOR_ADDRESS, 
		this->m_nBand)))
	{
		return result;
	}

	if(RFID_STATUS_OK !=
		(result = pRadio->GetConfigurationParameter(
		CONFIG_ADDRESS, 
		&config)))
	{
		return result;
	}

	if(RFID_STATUS_OK !=
		(result = pRadio->GetConfigurationParameter( 
		MULTDIV_ADDRESS, 
		&multdiv)))
	{
		return result;
	}

	if(RFID_STATUS_OK !=
		(result = pRadio->GetConfigurationParameter( 
		PLLCC_ADDRESS, 
		&pllcc)))
	{
		return result;
	}

	try
	{
		this->m_enumState = ( BandState ) ( config == 0 ? 0 : 1 );
	}
	catch ( CException* e)
	{
		this->m_enumState = UNKNOWN;
		e->ReportError();
	}


	this->m_nMultiplier   = ( INT16U ) ( ( multdiv >> 0  ) & 0xffff );
	this->m_nDivider      = ( INT16U ) ( ( multdiv >> 16 ) & 0xff   );

	this->m_nMinDACBand   = ( INT16U ) ( ( pllcc >> 0  ) & 0xff );
	this->m_nAffinityBand = ( INT16U ) ( ( pllcc >> 8  ) & 0xff );
	this->m_nMaxDACBand   = ( INT16U ) ( ( pllcc >> 16 ) & 0xff );
	this->m_nGuardBand    = ( INT16U ) ( ( pllcc >> 24 ) & 0xff );

	return result;
}

RFID_STATUS CFrequencyBand::Store(CRFIDRadio* pRadio)
{
	RFID_STATUS result = RFID_STATUS_OK;

	INT32U config    = this->m_enumState;
	INT32U multdiv   = ( INT32U ) ( this->m_nDivider      << 16 ) | ( INT32U ) this->m_nMultiplier;
	INT32U pllcc     = ( INT32U ) ( this->m_nGuardBand    << 24 ) |
		( INT32U ) ( this->m_nMaxDACBand   << 16 ) |
		( INT32U ) ( this->m_nAffinityBand << 8  ) |
		( INT32U ) ( this->m_nMinDACBand         ) ;

	if(RFID_STATUS_OK !=
		(result = pRadio->SetConfigurationParameter( 
		SELECTOR_ADDRESS, 
		this->m_nBand)))
	{
		return result;
	}

	if(RFID_STATUS_OK !=
		(result = pRadio->SetConfigurationParameter( 
		CONFIG_ADDRESS, 
		config)))
	{
		return result;
	}

	if(RFID_STATUS_OK !=
		(result = pRadio->GetConfigurationParameter( 
		CONFIG_ADDRESS, 
		&config)))


	if ( ENABLED == ( BandState ) config )
	{
		if(RFID_STATUS_OK !=
			(result = pRadio->SetConfigurationParameter( 
			MULTDIV_ADDRESS, 
			multdiv)))
		{
			return result;
		}

		if(RFID_STATUS_OK !=
			(result = pRadio->GetConfigurationParameter( 
			MULTDIV_ADDRESS, 
			&multdiv)))
		{
			return result;
		}

		if(RFID_STATUS_OK !=
			(result = pRadio->SetConfigurationParameter( 
			PLLCC_ADDRESS, 
			pllcc)))
		{
			return result;
		}

		if(RFID_STATUS_OK !=
			(result = pRadio->GetConfigurationParameter( 
			PLLCC_ADDRESS, 
			&pllcc)))
		{
			return result;
		}
	}

	this->m_nMultiplier   = ( INT16U ) ( ( multdiv >>  0 ) & 0xffff );
	this->m_nDivider      = ( INT16U ) ( ( multdiv >> 16 ) & 0xff   );

	this->m_nMinDACBand   = ( INT16U ) ( ( pllcc >>  0 ) & 0xff );
	this->m_nAffinityBand = ( INT16U ) ( ( pllcc >>  8 ) & 0xff );
	this->m_nMaxDACBand   = ( INT16U ) ( ( pllcc >> 16 ) & 0xff );
	this->m_nGuardBand    = ( INT16U ) ( ( pllcc >> 24 ) & 0xff );

	return result;
}

double CFrequencyBand::Frequency()
{
	return ( ClockKHz / ( 4 * this->m_nDivider ) ) * this->m_nMultiplier / 1000;
}
