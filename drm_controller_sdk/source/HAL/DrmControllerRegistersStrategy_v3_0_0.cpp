/**
*  \file      DrmControllerRegistersStrategy_v3_0_0.cpp
*  \version   4.0.1.0
*  \date      January 2020
*  \brief     Class DrmControllerRegistersStrategy_v3_0_0 defines strategy for register access of drm controller v3.0.0.
*  \copyright Licensed under the Apache License, Version 2.0 (the "License") {

}
*             you may not use this file except in compliance with the License.
*             You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*             Unless required by applicable law or agreed to in writing, software
*             distributed under the License is distributed on an "AS IS" BASIS,
*             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*             See the License for the specific language governing permissions and
*             limitations under the License.
**/

#include <HAL/DrmControllerRegistersStrategy_v3_0_0.hpp>

// name space usage
using namespace DrmControllerLibrary;

/************************************************************/
/**                  PUBLIC MEMBER FUNCTIONS               **/
/************************************************************/

/** DrmControllerRegistersStrategy_v3_0_0
*   \brief Class constructor.
*   \param[in] readRegisterFunction function pointer to read 32 bits register.
*              The function pointer shall have the following prototype "unsigned int f(const std::string&, unsigned int&)".
*   \param[in] writeRegisterFunction function pointer to write 32 bits register.
*              The function pointer shall have the following prototype "unsigned int f(const std::string&, unsigned int)".
**/
DrmControllerRegistersStrategy_v3_0_0::DrmControllerRegistersStrategy_v3_0_0(tDrmReadRegisterFunction readRegisterFunction,
                                                                             tDrmWriteRegisterFunction writeRegisterFunction)
: DrmControllerRegistersStrategyInterface(readRegisterFunction, writeRegisterFunction),
  mCommandRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_COMMAND_SIZE)),
  mLicenseStartAddressRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_LICENSE_START_ADDRESS_SIZE)),
  mLicenseTimerRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_LICENSE_TIMER_SIZE)),
  mStatusRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_STATUS_SIZE)),
  mErrorRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_ERROR_SIZE)),
  mDnaRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_DEVICE_DNA_SIZE)),
  mSaasChallengeRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_SAAS_CHALLENGE_SIZE)),
  mVersionRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_VERSION_SIZE)),
  mVlnvWordRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_VLNV_WORD_SIZE)),
  mLicenseWordRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_LICENSE_WORD_SIZE)),
  mTraceWordRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_TRACE_WORD_SIZE)),
  mMeteringWordRegisterWordNumber(numberOfWords(DRM_CONTROLLER_V3_0_0_METERING_WORD_SIZE)),
  mCommandRegisterStartIndex(0),
  mLicenseStartAddressRegisterStartIndex(mCommandRegisterStartIndex+mCommandRegisterWordNumber),
  mLicenseTimerRegisterStartIndex(mLicenseStartAddressRegisterStartIndex+mLicenseStartAddressRegisterWordNumber),
  mStatusRegisterStartIndex(mLicenseTimerRegisterStartIndex+mLicenseTimerRegisterWordNumber),
  mErrorRegisterStartIndex(mStatusRegisterStartIndex+mStatusRegisterWordNumber),
  mDnaRegisterStartIndex(mErrorRegisterStartIndex+mErrorRegisterWordNumber),
  mSaasChallengeRegisterStartIndex(mDnaRegisterStartIndex+mDnaRegisterWordNumber),
  mVersionRegisterStartIndex(mSaasChallengeRegisterStartIndex+mSaasChallengeRegisterWordNumber),
  mLogsRegisterStartIndex(mVersionRegisterStartIndex+mVersionRegisterWordNumber),
  mVlnvWordRegisterStartIndex(0),
  mLicenseWordRegisterStartIndex(0),
  mTraceWordRegisterStartIndex(0),
  mMeteringWordRegisterStartIndex(0),
  mNumberOfTracesPerIp(DRM_CONTROLLER_V3_0_0_NUMBER_OF_TRACES_PER_IP),
  mVlnvNumberOfAdditionalWords(DRM_CONTROLLER_V3_0_0_VLNV_NUMBER_OF_ADDITIONAL_WORDS),
  mMeteringNumberOfAdditionalWords(DRM_CONTROLLER_V3_0_0_METERING_NUMBER_OF_ADDITIONAL_WORDS),
  mLicenseFileHeaderWordNumber(DRM_CONTROLLER_V3_0_0_LICENSE_HEADER_BLOCK_SIZE),
  mLicenseFileIpBlockWordNumber(DRM_CONTROLLER_V3_0_0_LICENSE_IP_BLOCK_SIZE),
  mLicenseFileMinimumWordNumber((mLicenseFileHeaderWordNumber+mLicenseFileIpBlockWordNumber)*mLicenseWordRegisterWordNumber),
  mDrmErrorRegisterMessagesArraySize(DRM_CONTROLLER_V3_0_0_NUMBER_OF_ERROR_CODES),
  mDrmErrorRegisterMessagesArray({
    { mDrmErrorNotReady,                                   "Not ready" },
    { mDrmErrorNoError,                                    "No error"  },
    { mDrmErrorBusReadAuthenticatorDrmVersionTimeOutError, "Bus read authenticator drm version timeout error" },
    { mDrmErrorAuthenticatorDrmVersionError,               "Authenticator drm version error" },
    { mDrmErrorDnaAuthenticationError,                     "Authenticator authentication error" },
    { mDrmErrorBusWriteAuthenticatorCommandTimeOutError,   "Bus write authenticator command timeout error" },
    { mDrmErrorBusReadAuthenticatorStatusTimeOutError,     "Bus read authenticator status timeout error" },
    { mDrmErrorBusWriteAuthenticatorChallengeTimeOutError, "Bus write authenticator challenge timeout error" },
    { mDrmErrorBusReadAuthenticatorResponseTimeOutError,   "Bus read authenticator response timeout error" },
    { mDrmErrorBusReadAuthenticatorDnaTimeOutError,        "Bus read authenticator dna timeout error" },
    { mDrmErrorBusReadActivatorDrmVersionTimeOutError,     "Bus read activator drm version timeout error" },
    { mDrmErrorActivatorDrmVersionError,                   "Activator drm version error" },
    { mDrmErrorLicenseHeaderCheckError,                    "License header check error" },
    { mDrmErrorLicenseDrmVersionError,                     "License drm version error" },
    { mDrmErrorLicenseDnaDeltaError,                       "License dna delta error" },
    { mDrmErrorLicenseMacCheckError,                       "License MAC check error" },
    { mDrmErrorBusWriteActivatorCommandTimeOutError,       "Bus write activator command timeout error" },
    { mDrmErrorBusReadActivatorStatusTimeOutError,         "Bus read activator status timeout error" },
    { mDrmErrorBusReadActivatorChallengeTimeOutError,      "Bus read activator challenge timeout error" },
    { mDrmErrorBusWriteActivatorResponseTimeOutError,      "Bus write activator response timeout error" },
    { mDrmErrorBusReadInterruptTimeOutError,               "Bus read interrupt timeout error" },
    { mDrmErrorBusReadExpectedStatusError,                 "Bus read expected status error" }
  })
{
  setIndexedRegisterName(DRM_CONTROLLER_V3_0_0_INDEXED_REGISTER_NAME);
}

/** ~DrmControllerRegistersStrategy_v3_0_0
*   \brief Class destructor.
**/
DrmControllerRegistersStrategy_v3_0_0::~DrmControllerRegistersStrategy_v3_0_0()
{}

/** writeRegistersPageRegister
*   \brief Write the page register to select the registers page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeRegistersPageRegister() const {
  return writePageRegister(mDrmPageRegisters);
}

/** writeVlnvFilePageRegister
*   \brief Write the page register to select the vlnv file page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeVlnvFilePageRegister() const {
  return writePageRegister(mDrmPageVlnvFile);
}

/** writeLicenseFilePageRegister
*   \brief Write the page register to select the license file page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeLicenseFilePageRegister() const {
  return writePageRegister(mDrmPageLicenseFile);
}

/** writeTraceFilePageRegister
*   \brief Write the page register to select the trace file page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeTraceFilePageRegister() const {
  return writePageRegister(mDrmPageTraceFile);
}

/** writeMeteringFilePageRegister
*   \brief Write the page register to select the metering file page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeMeteringFilePageRegister() const {
  return writePageRegister(mDrmPageMeteringFile);
}

/** writeMailBoxFilePageRegister
*   \brief Write the page register to select the mailbox file page.
*   This method will access to the system bus to write into the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeMailBoxFilePageRegister() const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** writeNopCommandRegister
*   \brief Write the command register to the NOP Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeNopCommandRegister() const {
  return writeCommandRegister(mDrmCommandNop);
}

/** writeDnaExtractCommandRegister
*   \brief Write the command register to the DNA Extract Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeDnaExtractCommandRegister() const {
  return writeCommandRegister(mDrmCommandExtractDna);
}

/** writeVlnvExtractCommandRegister
*   \brief Write the command register to the VLNV Extract Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeVlnvExtractCommandRegister() const {
  return writeCommandRegister(mDrmCommandExtractVlnv);
}

/** writeActivateCommandRegister
*   \brief Write the command register to the Activate Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeActivateCommandRegister() const {
  return writeCommandRegister(mDrmCommandActivate);
}

/** writeEndSessionMeteringExtractCommandRegister
*   \brief Write the command register to the end session extract metering Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeEndSessionMeteringExtractCommandRegister() const {
  return writeCommandRegister(mDrmCommandEndSessionExtractMetering);
}

/** writeMeteringExtractCommandRegister
*   \brief Write the command register to the extract metering Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeMeteringExtractCommandRegister() const {
  throwUnsupportedFeatureException("asynchronous metering file extraction", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** writeSampleLicenseTimerCounterCommandRegister
*   \brief Write the command register to the sample license timer counter Command.
*   This method will access to the system bus to write into the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeSampleLicenseTimerCounterCommandRegister() const {
  throwUnsupportedFeatureException("asynchronous license timer counter sampling", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readLicenseStartAddressRegister
*   \brief Read the license start address register.
*   This method will access to the system bus to read the license start address.
*   \param[out] licenseStartAddress is a list of binary values for the license start address register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseStartAddressRegister(std::vector<unsigned int> &licenseStartAddress) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mLicenseStartAddressRegisterStartIndex, mLicenseStartAddressRegisterWordNumber, licenseStartAddress);
}

/** writeLicenseStartAddressRegister
*   \brief Write the license start address register.
*   This method will access to the system bus to write the license start address.
*   \param[in] licenseStartAddress is a list of binary values for the license start address register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeLicenseStartAddressRegister(const std::vector<unsigned int> &licenseStartAddress) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  std::vector<unsigned int> readLicenseStartAddress;
  errorCode = readLicenseStartAddressRegister(readLicenseStartAddress);
  if (errorCode != mDrmApi_NO_ERROR || readLicenseStartAddress == licenseStartAddress) return errorCode;
  return writeRegisterListFromIndex(mLicenseStartAddressRegisterStartIndex, mLicenseStartAddressRegisterWordNumber, licenseStartAddress);
}

/** readLicenseTimerInitRegister
*   \brief Read the license timer register.
*   This method will access to the system bus to read the license timer.
*   \param[out] licenseTimerInit is a list of binary values for the license timer register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerInitRegister(std::vector<unsigned int> &licenseTimerInit) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mLicenseTimerRegisterStartIndex, mLicenseTimerRegisterWordNumber, licenseTimerInit);
}

/** writeLicenseTimerInitRegister
*   \brief Write the license start address register.
*   This method will access to the system bus to write the license timer.
*   \param[in] licenseTimerInit is a list of binary values for the license timer register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeLicenseTimerInitRegister(const std::vector<unsigned int> &licenseTimerInit) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  std::vector<unsigned int> readLicenseTimerInit;
  errorCode = readLicenseTimerInitRegister(readLicenseTimerInit);
  if (errorCode != mDrmApi_NO_ERROR || readLicenseTimerInit == licenseTimerInit) return errorCode;
  return writeRegisterListFromIndex(mLicenseTimerRegisterStartIndex, mLicenseTimerRegisterWordNumber, licenseTimerInit);
}

/** readDnaReadyStatusRegister
*   \brief Read the status register and get the dna ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] dnaReady is the value of the status bit DNA Ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readDnaReadyStatusRegister(bool &dnaReady) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusDnaReady, mDrmStatusMaskDnaReady, dnaReady);
}

/** waitDnaReadyStatusRegister
*   \brief Wait dna ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitDnaReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusDnaReady, mDrmStatusMaskDnaReady, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Dna Ready Status is in timeout", "Expected Dna Ready Status", "Actual Dna Ready Status", expected, actual);
  return errorCode;
}

/** readVlnvReadyStatusRegister
*   \brief Read the status register and get the vlnv ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] vlnvReady is the value of the status bit VLNV Ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readVlnvReadyStatusRegister(bool &vlnvReady) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusVlnvReady, mDrmStatusMaskVlnvReady, vlnvReady);
}

/** waitVlnvReadyStatusRegister
*   \brief Wait vlnv ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitVlnvReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusVlnvReady, mDrmStatusMaskVlnvReady, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Vlnv Ready Status is in timeout", "Expected Vlnv Ready Status", "Actual Vlnv Ready Status", expected, actual);
  return errorCode;
}

/** readActivationDoneStatusRegister
*   \brief Read the status register and get the activation done status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] activationDone is the value of the status bit Activation Done.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readActivationDoneStatusRegister(bool &activationDone) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusActivationDone, mDrmStatusMaskActivationDone, activationDone);
}

/** waitActivationDoneStatusRegister
*   \brief Wait activation done status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitActivationDoneStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusActivationDone, mDrmStatusMaskActivationDone, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Activation Done Status is in timeout", "Expected Activation Done Status", "Actual Activation Done Status", expected, actual);
  return errorCode;
}

/** readAutonomousControllerEnabledStatusRegister
*   \brief Read the status register and get the autonomous controller enabled status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] autoEnabled is the value of the status bit autonomous controller enabled.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readAutonomousControllerEnabledStatusRegister(bool &autoEnabled) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusAutoEnabled, mDrmStatusMaskAutoEnabled, autoEnabled);

}

/** readAutonomousControllerBusyStatusRegister
*   \brief Read the status register and get the autonomous controller busy status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] autoBusy is the value of the status bit autonomous controller busy.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readAutonomousControllerBusyStatusRegister(bool &autoBusy) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusAutoBusy, mDrmStatusMaskAutoBusy, autoBusy);
}

/** waitAutonomousControllerBusyStatusRegister
*   \brief Wait autonomous controller busy status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitAutonomousControllerBusyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusAutoBusy, mDrmStatusMaskAutoBusy, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Autonomous Controller Busy Status is in timeout", "Expected Autonomous Controller Busy Status", "Actual Autonomous Controller Busy Status", expected, actual);
  return errorCode;
}

/** readMeteringEnabledStatusRegister
*   \brief Read the status register and get the metering enabled status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] meteringEnabled is the value of the status bit metering enabled.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMeteringEnabledStatusRegister(bool &meteringEnabled) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusMeteringEnabled, mDrmStatusMaskMeteringEnabled, meteringEnabled);

}

/** readMeteringReadyStatusRegister
*   \brief Read the status register and get the metering ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] meteringReady is the value of the status bit metering ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMeteringReadyStatusRegister(bool &meteringReady) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusMeteringReady, mDrmStatusMaskMeteringReady, meteringReady);
}

/** waitMeteringReadyStatusRegister
*   \brief Wait metering ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitMeteringReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusMeteringReady, mDrmStatusMaskMeteringReady, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Metering Ready Status is in timeout", "Expected Metering Ready Status", "Actual Metering Ready Status", expected, actual);
  return errorCode;
}

/** readSaasChallengeReadyStatusRegister
*   \brief Read the status register and get the saas challenge ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] saasChallengeReady is the value of the status bit saas challenge ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readSaasChallengeReadyStatusRegister(bool &saasChallengeReady) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusSaasChallengeReady, mDrmStatusMaskSaasChallengeReady, saasChallengeReady);
}

/** waitSaasChallengeReadyStatusRegister
*   \brief Wait saas challenge ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitSaasChallengeReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusSaasChallengeReady, mDrmStatusMaskSaasChallengeReady, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Saas Challenge Ready Status is in timeout", "Expected Saas Challenge Ready Status", "Actual Saas Challenge Ready Status", expected, actual);
  return errorCode;
}

/** readLicenseTimerEnabledStatusRegister
*   \brief Read the status register and get the license timer enabled status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseTimerEnabled is the value of the status bit license timer enabled.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerEnabledStatusRegister(bool &licenseTimerEnabled) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusLicenseTimerEnabled, mDrmStatusMaskLicenseTimerEnabled, licenseTimerEnabled);
}

/** readLicenseTimerInitLoadedStatusRegister
*   \brief Read the status register and get the license timer init loaded status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseTimerInitLoaded is the value of the status bit license timer init load.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerInitLoadedStatusRegister(bool &licenseTimerInitLoaded) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusLicenseTimerInitLoaded, mDrmStatusMaskLicenseTimerInitLoaded, licenseTimerInitLoaded);
}

/** waitLicenseTimerInitLoadedStatusRegister
*   \brief Wait license timer init loaded status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseTimerInitLoadedStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusLicenseTimerInitLoaded, mDrmStatusMaskLicenseTimerInitLoaded, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait License Timer Init Loaded Status is in timeout", "Expected License Timer Init Loaded Status", "Actual License Timer Init Loaded Status", expected, actual);
  return errorCode;
}

/** readEndSessionMeteringReadyStatusRegister
*   \brief Read the status register and get the end session metering ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] endSessionMeteringReady is the value of the status bit end session metering ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readEndSessionMeteringReadyStatusRegister(bool &endSessionMeteringReady) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusEndSessionMeteringReady, mDrmStatusMaskEndSessionMeteringReady, endSessionMeteringReady);
}

/** waitEndSessionMeteringReadyStatusRegister
*   \brief Wait end session metering ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitEndSessionMeteringReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitStatusRegister(timeout, mDrmStatusEndSessionMeteringReady, mDrmStatusMaskEndSessionMeteringReady, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait End Session Metering Ready Status is in timeout", "Expected End Session Metering Ready Status", "Actual End Session Metering Ready Status", expected, actual);
  return errorCode;
}

/** readHeartBeatModeEnabledStatusRegister
*   \brief Read the status register and get the heart beat mode enabled status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] heartBeatModeEnabled is the value of the status bit heart beat mode enabled.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readHeartBeatModeEnabledStatusRegister(bool &heartBeatModeEnabled) const {
  throwUnsupportedFeatureException("heart mode enabled status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readAsynchronousMeteringReadyStatusRegister
*   \brief Read the status register and get the asynchronous metering ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] asynchronousMeteringReady is the value of the status bit asynchronous metering ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readAsynchronousMeteringReadyStatusRegister(bool &asynchronousMeteringReady) const {
  throwUnsupportedFeatureException("asynchronous metering ready status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitAsynchronousMeteringReadyStatusRegister
*   \brief Wait asynchronous metering ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitAsynchronousMeteringReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("asynchronous metering ready status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readLicenseTimerSampleReadyStatusRegister
*   \brief Read the status register and get the license timer sample ready status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseTimerSampleReady is the value of the status bit license timer sample ready.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerSampleReadyStatusRegister(bool &licenseTimerSampleReady) const {
  throwUnsupportedFeatureException("license timer count sample ready status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitLicenseTimerSampleReadyStatusRegister
*   \brief Wait license timer sample ready status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseTimerSampleReadyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("license timer count sample ready status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readLicenseTimerCountEmptyStatusRegister
*   \brief Read the status register and get the license timer count empty status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseTimerCounterEmpty is the value of the status bit license timer count empty.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerCountEmptyStatusRegister(bool &licenseTimerCounterEmpty) const {
  throwUnsupportedFeatureException("license timer count empty status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitLicenseTimerCountEmptyStatusRegister
*   \brief Wait license timer count empty status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseTimerCountEmptyStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("license timer count empty status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readSessionRunningStatusRegister
*   \brief Read the status register and get the session running status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] sessionRunning is the value of the status bit session running.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readSessionRunningStatusRegister(bool &sessionRunning) const {
  throwUnsupportedFeatureException("session running status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitSessionRunningStatusRegister
*   \brief Wait session running status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitSessionRunningStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("session running status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readActivationCodesTransmittedStatusRegister
*   \brief Read the status register and get the activation codes transmitted status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] activationCodeTransmitted is the value of the status bit activation codes transmitted.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readActivationCodesTransmittedStatusRegister(bool &activationCodeTransmitted) const {
  throwUnsupportedFeatureException("activation codes transmitted status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitActivationCodesTransmittedStatusRegister
*   \brief Wait activation codes transmitted status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitActivationCodesTransmittedStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("activation codes transmitted status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readLicenseNodeLockStatusRegister
*   \brief Read the status register and get the license node lock status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseNodeLock is the value of the status bit license node lock.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseNodeLockStatusRegister(bool &licenseNodeLock) const {
  throwUnsupportedFeatureException("license node lock status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitLicenseNodeLockStatusRegister
*   \brief Wait license node lock status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseNodeLockStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("license node lock status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readLicenseMeteringStatusRegister
*   \brief Read the status register and get the license metering status bit.
*   This method will access to the system bus to read the status register.
*   \param[out] licenseMetering is the value of the status bit license metering.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseMeteringStatusRegister(bool &licenseMetering) const {
  throwUnsupportedFeatureException("license metering status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitLicenseMeteringStatusRegister
*   \brief Wait license metering status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status bit read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseMeteringStatusRegister(const unsigned int &timeout, const bool &expected, bool &actual) const {
  throwUnsupportedFeatureException("license metering status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readNumberOfLicenseTimerLoadedStatusRegister
*   \brief Read the status register and get the number of license timer loaded.
*   This method will access to the system bus to read the status register.
*   \param[out] numberOfLicenseTimerLoaded is the number of license timer loaded retrieved from the status.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readNumberOfLicenseTimerLoadedStatusRegister(unsigned int &numberOfLicenseTimerLoaded) const {
  throwUnsupportedFeatureException("number of license timer loaded status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** waitNumberOfLicenseTimerLoadedStatusRegister
*   \brief Wait number of license timer loaded status register to reach specified value.
*   This method will access to the system bus to read the status register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the status to be expected.
*   \param[out] actual is the value of the status read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitNumberOfLicenseTimerLoadedStatusRegister(const unsigned int &timeout, const unsigned int &expected, unsigned int &actual) const {
  throwUnsupportedFeatureException("number of license timer loaded status", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readNumberOfDetectedIpsStatusRegister
*   \brief Read the status register and get the number of detected IPs.
*   This method will access to the system bus to read the status register.
*   \param[out] numberOfDetectedIps is the number of detected ips retrieved from the status.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readNumberOfDetectedIpsStatusRegister(unsigned int &numberOfDetectedIps) const {
  return DrmControllerRegistersStrategyInterface::readStatusRegister(mDrmStatusIpActivatorNumberLsb, mDrmStatusMaskIpActivatorNumber, numberOfDetectedIps);
}

/** readExtractDnaErrorRegister
*   \brief Read the error register and get the error code related to dna extraction.
*   This method will access to the system bus to read the error register.
*   \param[out] dnaExtractError is the error code related to dna extraction.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readExtractDnaErrorRegister(unsigned char &dnaExtractError) const {
  return DrmControllerRegistersStrategyInterface::readErrorRegister(mDrmDnaExtractErrorPosition, mDrmDnaExtractErrorMask, dnaExtractError);
}

/** waitExtractDnaErrorRegister
*   \brief Wait error to reach specified value.
*   This method will access to the system bus to read the error register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the error to be expected.
*   \param[out] actual is the value of the error read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitExtractDnaErrorRegister(const unsigned int &timeout, const unsigned char &expected, unsigned char &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitErrorRegister(timeout, mDrmDnaExtractErrorPosition, mDrmDnaExtractErrorMask, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Extract Dna Error is in timeout", "Expected Extract Dna Error", "Actual Extract Dna Error", expected, actual, getDrmErrorRegisterMessage(expected), getDrmErrorRegisterMessage(actual));
  return errorCode;
}

/** readExtractVlnvErrorRegister
*   \brief Read the error register and get the error code related to vlnv extraction.
*   This method will access to the system bus to read the error register.
*   \param[out] vlnvExtractError is the error code related to vlnv extraction.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readExtractVlnvErrorRegister(unsigned char &vlnvExtractError) const {
  return DrmControllerRegistersStrategyInterface::readErrorRegister(mDrmVlnvExtractErrorPosition, mDrmVlnvExtractErrorMask, vlnvExtractError);
}

/** waitExtractVlnvErrorRegister
*   \brief Wait error to reach specified value.
*   This method will access to the system bus to read the error register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the error to be expected.
*   \param[out] actual is the value of the error read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitExtractVlnvErrorRegister(const unsigned int &timeout, const unsigned char &expected, unsigned char &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitErrorRegister(timeout, mDrmVlnvExtractErrorPosition, mDrmVlnvExtractErrorMask, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Extract Vlnv Error is in timeout", "Expected Extract Vlnv Error", "Actual Extract Vlnv Error", expected, actual, getDrmErrorRegisterMessage(expected), getDrmErrorRegisterMessage(actual));
  return errorCode;
}

/** readActivationErrorRegister
*   \brief Read the error register and get the error code related to activation.
*   This method will access to the system bus to read the error register.
*   \param[out] activationError is the error code related to activation.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readActivationErrorRegister(unsigned char &activationError) const {
  return DrmControllerRegistersStrategyInterface::readErrorRegister(mDrmActivationErrorPosition, mDrmActivationErrorMask, activationError);
}

/** waitActivationErrorRegister
*   \brief Wait error to reach specified value.
*   This method will access to the system bus to read the error register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the error to be expected.
*   \param[out] actual is the value of the error read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitActivationErrorRegister(const unsigned int &timeout, const unsigned char &expected, unsigned char &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitErrorRegister(timeout, mDrmActivationErrorPosition, mDrmActivationErrorMask, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait Activation Error is in timeout", "Expected Activation Error", "Actual Activation Error", expected, actual, getDrmErrorRegisterMessage(expected), getDrmErrorRegisterMessage(actual));
  return errorCode;
}

/** readLicenseTimerLoadErrorRegister
*   \brief Read the error register and get the error code related to license timer loading.
*   This method will access to the system bus to read the error register.
*   \param[out] licenseTimerLoadError is the error code related to license timer loading.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerLoadErrorRegister(unsigned char &licenseTimerLoadError) const {
  return DrmControllerRegistersStrategyInterface::readErrorRegister(mDrmLicenseTimerLoadErrorPosition, mDrmLicenseTimerLoadErrorMask, licenseTimerLoadError);
}

/** waitActivationErrorRegister
*   \brief Wait error to reach specified value.
*   This method will access to the system bus to read the error register.
*   \param[in]  timeout is the timeout value in micro seconds.
*   \param[in]  expected is the value of the error to be expected.
*   \param[out] actual is the value of the error read.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_HARDWARE_TIMEOUT_ERROR if a timeout occured, errors from read/write register functions otherwise.
*   \throw DrmControllerTimeOutException whenever a timeout error occured. DrmControllerTimeOutException::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::waitLicenseTimerLoadErrorRegister(const unsigned int &timeout, const unsigned char &expected, unsigned char &actual) const {
  unsigned int errorCode = DrmControllerRegistersStrategyInterface::waitErrorRegister(timeout, mDrmLicenseTimerLoadErrorPosition, mDrmLicenseTimerLoadErrorMask, expected, actual);
  if (errorCode == mDrmApi_HARDWARE_TIMEOUT_ERROR)
    throwTimeoutException("Wait License Timer Load Error is in timeout", "Expected License Timer Load Error", "Actual License Timer Load Error", expected, actual, getDrmErrorRegisterMessage(expected), getDrmErrorRegisterMessage(actual));
  return errorCode;
}

/** readDnaRegister
*   \brief Read the dna register and get the value.
*   This method will access to the system bus to read the dna register.
*   \param[out] dna is the dna value.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readDnaRegister(std::vector<unsigned int> &dna) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mDnaRegisterStartIndex, mDnaRegisterWordNumber, dna);
}

/** readSaasChallengeRegister
*   \brief Read the Saas Challenge register and get the value.
*   This method will access to the system bus to read the Saas Challenge register.
*   \param[out] saasChallenge is the saas challenge value.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readSaasChallengeRegister(std::vector<unsigned int> &saasChallenge) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mSaasChallengeRegisterStartIndex, mSaasChallengeRegisterWordNumber, saasChallenge);
}

/** readLicenseTimerCounterRegister
*   \brief Read the License Timer Counter register and get the value.
*   This method will access to the system bus to read the License Timer Counter register.
*   \param[out] licenseTimerCounter is the License Timer Counter value.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseTimerCounterRegister(std::vector<unsigned int> &licenseTimerCounter) const {
  throwUnsupportedFeatureException("asynchronous license timer counter sampling", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readDrmVersionRegister
*   \brief Read the drm version register and get the value.
*   This method will access to the system bus to read the drm version register.
*   \param[out] drmVersion is the drm version value.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readDrmVersionRegister(unsigned int &drmVersion) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterAtIndex(mVersionRegisterStartIndex, drmVersion);
}

/** readLogsRegister
*   \brief Read the logs register and get the value.
*   This method will access to the system bus to read the logs register.
*   \param[in] numberOfIps is the total number of IPs.
*   \param[out] logs is the logs value.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLogsRegister(const unsigned int &numberOfIps, std::vector<unsigned int> &logs) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mLogsRegisterStartIndex, numberOfWords(numberOfIps), logs);
}

/** readVlnvFileRegister
*   \brief Read the vlnv file and get the value.
*   This method will access to the system bus to read the vlnv file.
*   The vlnv file will contains numberOfIps+1 words. The first one
*   is dedicated to the drm controller, the others correspond for
*   the IPs connected to the drm controller.
*   \param[in] numberOfIps is the total number of IPs.
*   \param[out] vlnvFile is the vlnv file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readVlnvFileRegister(const unsigned int &numberOfIps, std::vector<unsigned int> &vlnvFile) const {
  unsigned int errorCode = writeVlnvFilePageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mVlnvWordRegisterStartIndex, mVlnvWordRegisterWordNumber*(numberOfIps+mVlnvNumberOfAdditionalWords), vlnvFile);
}

/** readVlnvFileRegister
*   \brief Read the vlnv file and get the value.
*   This method will access to the system bus to read the vlnv file.
*   The vlnv file will contains numberOfIps+1 elements. The first one
*   is dedicated to the drm controller, the others correspond for
*   the IPs connected to the drm controller.
*   \param[in] numberOfIPs is the total number of IPs.
*   \param[out] vlnvFile is the vlnv file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readVlnvFileRegister(const unsigned int &numberOfIPs, std::vector<std::string> &vlnvFile) const {
  std::vector<unsigned int> tmpVlnvFile;
  unsigned int errorCode = readVlnvFileRegister(numberOfIPs, tmpVlnvFile);
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  vlnvFile = DrmControllerDataConverter::binaryToHexStringList(tmpVlnvFile, mVlnvWordRegisterWordNumber);
  return errorCode;
}

/** readLicenseFileRegister
*   \brief Read the license file and get the value.
*   This method will access to the system bus to read the license file.
*   \param[in] licenseFileSize is the number of 128 bits words to read.
*   \param[out] licenseFile is the license file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseFileRegister(const unsigned int &licenseFileSize, std::vector<unsigned int> &licenseFile) const {
  unsigned int errorCode = writeLicenseFilePageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mLicenseWordRegisterStartIndex, mLicenseWordRegisterWordNumber*licenseFileSize, licenseFile);
}

/** readLicenseFileRegister
*   \brief Read the license file and get the value.
*   This method will access to the system bus to read the license file.
*   The license file is a string using a hexadecimal representation.
*   \param[in] licenseFileSize is the number of 128 bits words to read.
*   \param[out] licenseFile is the license file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readLicenseFileRegister(const unsigned int &licenseFileSize, std::string &licenseFile) const {
  std::vector<unsigned int> tmpLicense;
  unsigned int errorCode = readLicenseFileRegister(licenseFileSize, tmpLicense);
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  licenseFile = DrmControllerDataConverter::binaryToHexString(tmpLicense);
  return errorCode;
}

/** writeLicenseFile
*   \brief Write the license file.
*   This method will access to the system bus to write the license file.
*   \param[in] licenseFileSize is the number of 128 bits words to read.
*   \param[in] licenseFile is the license file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeLicenseFileRegister(const unsigned int &licenseFileSize, const std::vector<unsigned int> &licenseFile) const {
  unsigned int errorCode = writeLicenseFilePageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  std::vector<unsigned int> readLicenseFile;
  errorCode = readLicenseFileRegister(licenseFileSize, readLicenseFile);
  if (errorCode != mDrmApi_NO_ERROR || readLicenseFile == licenseFile) return errorCode;
  return writeRegisterListFromIndex(mLicenseWordRegisterStartIndex, mLicenseWordRegisterWordNumber*licenseFileSize, licenseFile);
}

/** writeLicenseFileRegister
*   \brief Write the license file.
*   This method will access to the system bus to write the license file.
*   The license file is a string using a hexadecimal representation.
*   \param[in] licenseFile is the license file.
*   \return Returns mDrmApi_NO_ERROR if no error,
*           mDrmApi_LICENSE_FILE_SIZE_ERROR if the license file size is lower than the minimum required,
*           or the error code produced by the read/write register function.
*   \throw DrmControllerLicenseFileSizeException whenever a check on license file size is bad. DrmControllerLicenseFileSizeException::what()
*          should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeLicenseFileRegister(const std::string &licenseFile) const {
  std::vector<unsigned int> tmpLicenseFile = DrmControllerDataConverter::hexStringToBinary(licenseFile);
  if (checkLicenseFileSize(tmpLicenseFile) == false) return mDrmApi_LICENSE_FILE_SIZE_ERROR;
  unsigned int licenseFileSize = tmpLicenseFile.size()/mLicenseWordRegisterWordNumber;
  return writeLicenseFileRegister(licenseFileSize, tmpLicenseFile);
}

/** readTraceFileRegister
*   \brief Read the trace file and get the value.
*   This method will access to the system bus to read the trace file.
*   \param[in] numberOfIps is the total number of IPs.
*   \param[out] traceFile is the trace file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readTraceFileRegister(const unsigned int &numberOfIps, std::vector<unsigned int> &traceFile) const {
  unsigned int errorCode = writeTraceFilePageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mTraceWordRegisterStartIndex, mTraceWordRegisterWordNumber*numberOfIps*mNumberOfTracesPerIp, traceFile);
}

/** readTraceFileRegister
*   \brief Read the trace file and get the value.
*   This method will access to the system bus to read the trace file.
*   \param[in] numberOfIPs is the total number of IPs.
*   \param[out] traceFile is the trace file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readTraceFileRegister(const unsigned int &numberOfIPs, std::vector<std::string> &traceFile) const {
  std::vector<unsigned int> tmpTraceFile;
  unsigned int errorCode = readTraceFileRegister(numberOfIPs, tmpTraceFile);
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  traceFile = DrmControllerDataConverter::binaryToHexStringList(tmpTraceFile, mTraceWordRegisterWordNumber);
  return errorCode;
}

/** readMeteringFileRegister
*   \brief Read the metering file and get the value.
*   This method will access to the system bus to read the metering file.
*   \param[in] numberOfIps is the total number of IPs.
*   \param[out] meteringFile is the metering file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMeteringFileRegister(const unsigned int &numberOfIps, std::vector<unsigned int> &meteringFile) const {
  unsigned int errorCode = writeMeteringFilePageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterListFromIndex(mMeteringWordRegisterStartIndex, mMeteringWordRegisterWordNumber*(numberOfIps+mMeteringNumberOfAdditionalWords), meteringFile);
}

/** readMeteringFileRegister
*   \brief Read the metering file and get the value.
*   This method will access to the system bus to read the metering file.
*   \param[in] numberOfIPs is the total number of IPs.
*   \param[out] meteringFile is the metering file.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMeteringFileRegister(const unsigned int &numberOfIPs, std::vector<std::string> &meteringFile) const {
  std::vector<unsigned int> tmpMeteringFile;
  unsigned int errorCode = readMeteringFileRegister(numberOfIPs, tmpMeteringFile);
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  meteringFile = DrmControllerDataConverter::binaryToHexStringList(tmpMeteringFile, mMeteringWordRegisterWordNumber);
  return errorCode;
}

/** readMailboxFileSizeRegister
*   \brief Read the mailbox file word numbers.
*   This method will access to the system bus to read the mailbox file.
*   \param[out] readOnlyMailboxWordNumber is the number of words in the read-only mailbox.
*   \param[out] readWriteMailboxWordNumber is the number of words in the read-write mailbox.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMailboxFileSizeRegister(unsigned int &readOnlyMailboxWordNumber, unsigned int &readWriteMailboxWordNumber) const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readMailboxFileRegister
*   \brief Read the mailbox file.
*   This method will access to the system bus to read the mailbox file.
*   \param[out] readOnlyMailboxWordNumber is the number of words in the read-only mailbox.
*   \param[out] readWriteMailboxWordNumber is the number of words in the read-write mailbox.
*   \param[out] readOnlyMailboxData is the data read from the read-only mailbox.
*   \param[out] readWriteMailboxData is the data read from the read-write mailbox.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMailboxFileRegister(unsigned int &readOnlyMailboxWordNumber, unsigned int &readWriteMailboxWordNumber,
                                                                            std::vector<unsigned int> &readOnlyMailboxData, std::vector<unsigned int> &readWriteMailboxData) const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** readMailboxFileRegister
*   \brief Read the mailbox file.
*   This method will access to the system bus to read the mailbox file.
*   \param[out] readOnlyMailboxWordNumber is the number of words in the read-only mailbox.
*   \param[out] readWriteMailboxWordNumber is the number of words in the read-write mailbox.
*   \param[out] readOnlyMailboxData is the data read from the read-only mailbox.
*   \param[out] readWriteMailboxData is the data read from the read-write mailbox.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readMailboxFileRegister(unsigned int &readOnlyMailboxWordNumber, unsigned int &readWriteMailboxWordNumber,
                                                                            std::vector<std::string> &readOnlyMailboxData, std::vector<std::string> &readWriteMailboxData) const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** writeMailboxFileRegister
*   \brief Write the mailbox file.
*   This method will access to the system bus to write the mailbox file.
*   \param[in] readWriteMailboxData is the data to write into the read-write mailbox.
*   \param[out] readWriteMailboxWordNumber is the number of words in the read-write mailbox.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeMailboxFileRegister(const std::vector <unsigned int> &readWriteMailboxData, unsigned int &readWriteMailboxWordNumber) const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** writeMailboxFileRegister
*   \brief Write the mailbox file.
*   This method will access to the system bus to write the mailbox file.
*   \param[in] readWriteMailboxData is the data to write into the read-write mailbox.
*   \param[out] readWriteMailboxWordNumber is the number of words in the read-write mailbox.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeMailboxFileRegister(const std::vector<std::string> &readWriteMailboxData, unsigned int &readWriteMailboxWordNumber) const {
  throwUnsupportedFeatureException("mailbox file", DRM_CONTROLLER_V3_0_0_SUPPORTED_VERSION);
  return mDrmApi_UNSUPPORTED_FEATURE_ERROR;
}

/** printMeteringFile
*   \brief Display the value of the metering file.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printMeteringFileHwReport(std::ostream &file) const {
  unsigned int numberOfDetectedIps;
  std::vector<std::string> meteringFile;
  if (readNumberOfDetectedIpsStatusRegister(numberOfDetectedIps) != mDrmApi_NO_ERROR) return;
  if (readMeteringFileRegister(numberOfDetectedIps, meteringFile) != mDrmApi_NO_ERROR) return;
  file << fileName("ENCRYPTED METERING") << std::endl;
  file << registerValue(meteringFile, "METERING", 0) << std::endl;
}

/** getDrmErrorRegisterMessage
*   \brief Get the error message from the error register value.
*   \param[in] errorRegister is the value of the error register.
*   \return Returns the error message.
**/
const char* DrmControllerRegistersStrategy_v3_0_0::getDrmErrorRegisterMessage(const unsigned char &errorRegister) const {
  for (unsigned int ii = 0; ii < mDrmErrorRegisterMessagesArraySize; ii++) {
    if (mDrmErrorRegisterMessagesArray[ii].mDrmErrorCode == errorRegister) {
      return mDrmErrorRegisterMessagesArray[ii].mDrmErrorMessage.c_str();
    }
  }
  return "Unknown error";
}

/************************************************************/
/**                  PROTECTED MEMBER FUNCTIONS            **/
/************************************************************/

/** readPageRegister
*   \brief Read and get the value of the page register from the hardware.
*   This method will access to the system bus to read the page register.
*   \param[out] page is the value of the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readPageRegister(unsigned int &page) const {
  return readRegister(DRM_CONTROLLER_V3_0_0_PAGE_REGISTER_NAME, page);
}

/** writePageRegister
*   \brief Write the value of the page register into the hardware.
*   This method will access to the system bus to write the page register.
*   \param[in] page is the value of the page register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writePageRegister(const unsigned int &page) const {
  unsigned int readPage;
  unsigned int errorCode = readPageRegister(readPage);
  if (errorCode != mDrmApi_NO_ERROR || readPage == page) return errorCode;
  return writeRegister(DRM_CONTROLLER_V3_0_0_PAGE_REGISTER_NAME, page);
}

/** readCommandRegister
*   \brief Read and get the value of the command register from the hardware.
*   This method will access to the system bus to read the command register.
*   \param[out] command is the value of the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readCommandRegister(unsigned int &command) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterAtIndex(mCommandRegisterStartIndex, command);
}

/** writeCommandRegister
*   \brief Write the value of the command register into the hardware.
*   This method will access to the system bus to write the command register.
*   \param[in] command is the value of the command register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::writeCommandRegister(const unsigned int &command) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  unsigned int readCommand;
  errorCode = readCommandRegister(readCommand);
  if (errorCode != mDrmApi_NO_ERROR || readCommand == command) return errorCode;
  return writeRegisterAtIndex(mCommandRegisterStartIndex, command);
}

/** readStatusRegister
*   \brief Read the status register.
*   This method will access to the system bus to read the status register.
*   \param[out] status is the binary value of the status register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readStatusRegister(unsigned int &status) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterAtIndex(mStatusRegisterStartIndex, status);
}

/** readErrorRegister
*   \brief Read the error register.
*   This method will access to the system bus to read the error register.
*   \param[out] error is the binary value of the error register.
*   \return Returns mDrmApi_NO_ERROR if no error, mDrmApi_UNSUPPORTED_FEATURE_ERROR if the feature is not supported, errors from read/write register functions otherwise.
*   \throw DrmControllerUnsupportedFeature whenever the feature is not supported. DrmControllerUnsupportedFeature::what() should be called to get the exception description.
**/
unsigned int DrmControllerRegistersStrategy_v3_0_0::readErrorRegister(unsigned int &error) const {
  unsigned int errorCode = writeRegistersPageRegister();
  if (errorCode != mDrmApi_NO_ERROR) return errorCode;
  return readRegisterAtIndex(mErrorRegisterStartIndex, error);
}

/************************************************************/
/**                  PRIVATE MEMBER FUNCTIONS              **/
/************************************************************/

/** checkLicenseFileSize
*   \brief Verify that the size of the license file is correct.
*   \param[in] licenseFile is the license file.
*   \return Returns true if license file size is correct, false otherwise.
*   \throw DrmControllerLicenseFileSizeException whenever a check on license file size is bad. DrmControllerLicenseFileSizeException::what() should be called to get the exception description.
**/
bool DrmControllerRegistersStrategy_v3_0_0::checkLicenseFileSize(const std::vector<unsigned int> &licenseFile) const {
  if (licenseFile.size() >= mLicenseFileMinimumWordNumber) return true;
  throwLicenseFileSizeException(mLicenseFileMinimumWordNumber, licenseFile.size());
  return false;
}

/** printPage
*   \brief Display the value of the page register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printPageHwReport(std::ostream &file) const {
  unsigned int page(0);
  if (readPageRegister(page) != mDrmApi_NO_ERROR) return;
  file << registerName("PAGE") << std::endl;
  file << registerValue(page, "PAGE", 1) << std::endl;
}

/** printCommand
*   \brief Display the value of the command register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printCommandHwReport(std::ostream &file) const {
  unsigned int command(0);
  if (readCommandRegister(command) != mDrmApi_NO_ERROR) return;
  file << registerName("COMMAND") << std::endl;
  file << registerValue(command, "COMMAND", 2) << std::endl;
}

/** printLicenseStartAddress
*   \brief Display the value of the license start address register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printLicenseStartAddressHwReport(std::ostream &file) const {
  std::string licenseStartAddress("");
  if (DrmControllerRegistersStrategyInterface::readLicenseStartAddressRegister(licenseStartAddress) != mDrmApi_NO_ERROR) return;
  file << registerName("LICENSE START ADDRESS") << std::endl;
  file << registerValue(licenseStartAddress, "LICENSE START ADDRESS") << std::endl;
}

/** printLicenseTimer
*   \brief Display the value of the license timer register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printLicenseTimerHwReport(std::ostream &file) const {
  std::string licenseTimerInit("");
  if (DrmControllerRegistersStrategyInterface::readLicenseTimerInitRegister(licenseTimerInit) != mDrmApi_NO_ERROR) return;
  file << registerName("LICENSE TIMER INIT") << std::endl;
  file << registerValue(licenseTimerInit.substr(0,  32), "LICENSE TIMER INIT WORD 0") << std::endl;
  file << registerValue(licenseTimerInit.substr(32, 32), "LICENSE TIMER INIT WORD 0") << std::endl;
  file << registerValue(licenseTimerInit.substr(64, 32), "LICENSE TIMER INIT WORD 0") << std::endl;
}

/** printStatus
*   \brief Display the value of the status register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printStatusHwReport(std::ostream &file) const {
  bool bitStatus(false);
  unsigned int intStatus(0);
  file << registerName("STATUS") << std::endl;
  //
  if (readDnaReadyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "DNA READY STATUS") << std::endl;
  //
  if (readVlnvReadyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "VLNV READY STATUS") << std::endl;
  //
  if (readActivationDoneStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "ACTIVATION DONE STATUS") << std::endl;
  //
  if (readAutonomousControllerEnabledStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "AUTONOMOUS CONTROLLER ENABLED STATUS") << std::endl;
  //
  if (readAutonomousControllerBusyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "AUTONOMOUS CONTROLLER BUSY STATUS") << std::endl;
  //
  if (readMeteringEnabledStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "METERING ENABLED STATUS") << std::endl;
  //
  if (readMeteringReadyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "METERING READY STATUS") << std::endl;
  //
  if (readSaasChallengeReadyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "SAAS CHALLENGE READY STATUS") << std::endl;
  //
  if (readLicenseTimerEnabledStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "LICENSE TIMER ENABLED STATUS") << std::endl;
  //
  if (readLicenseTimerInitLoadedStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "LICENSE TIMER INIT LOADED STATUS") << std::endl;
  //
  if (readEndSessionMeteringReadyStatusRegister(bitStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(bitStatus, "END SESSION METERING READY STATUS") << std::endl;
  //
  if (readNumberOfDetectedIpsStatusRegister(intStatus) != mDrmApi_NO_ERROR) return;
  file << registerValue(intStatus, "NUMBER OF DETECTED IPS STATUS") << std::endl;
}

/** printError
*   \brief Display the value of the error register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printErrorHwReport(std::ostream &file) const {
  unsigned char errorCode(0);
  file << registerName("STATUS") << std::endl;
  //
  if (readExtractDnaErrorRegister(errorCode) != mDrmApi_NO_ERROR) return;
  file << registerValue((unsigned int)errorCode, "DNA EXTRACT ERROR", 2) << std::endl;
  file << stringValue(getDrmErrorRegisterMessage(errorCode), "DNA EXTRACT ERROR MESSAGE") << std::endl;
  //
  if (readExtractVlnvErrorRegister(errorCode) != mDrmApi_NO_ERROR) return;
  file << registerValue((unsigned int)errorCode, "VLNV EXTRACT ERROR", 2) << std::endl;
  file << stringValue(getDrmErrorRegisterMessage(errorCode), "VLNV EXTRACT ERROR MESSAGE") << std::endl;
  //
  if (readLicenseTimerLoadErrorRegister(errorCode) != mDrmApi_NO_ERROR) return;
  file << registerValue((unsigned int)errorCode, "LICENSE TIMER LOAD ERROR", 2) << std::endl;
  file << stringValue(getDrmErrorRegisterMessage(errorCode), "LICENSE TIMER LOAD ERROR MESSAGE") << std::endl;
  //
  if (readActivationErrorRegister(errorCode) != mDrmApi_NO_ERROR) return;
  file << registerValue((unsigned int)errorCode, "ACTIVATION ERROR", 2) << std::endl;
  file << stringValue(getDrmErrorRegisterMessage(errorCode), "ACTIVATION ERROR MESSAGE") << std::endl;
}

/** printDrmVersion
*   \brief Display the value of the drm version.
**/
void DrmControllerRegistersStrategy_v3_0_0::printDrmVersionHwReport(std::ostream &file) const {
  std::string drmVersion;
  if (DrmControllerRegistersStrategyInterface::readDrmVersionRegister(drmVersion) != mDrmApi_NO_ERROR) return;
  file << versionName("SOFTWARE") << std::endl;
  file << stringValue(DRM_CONTROLLER_SDK_VERSION, "SDK VERSION") << std::endl;
  // display the hardware version
  std::string drmVersionDot = DrmControllerDataConverter::binaryToVersionString(DrmControllerDataConverter::hexStringToBinary(drmVersion)[0]);
  file << versionName("HARDWARE") << std::endl;
  file << stringValue(drmVersionDot, "HDK VERSION") << std::endl;
}

/** printDna
*   \brief Display the value of the dna.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printDnaHwReport(std::ostream &file) const {
  std::string dna;
  if (DrmControllerRegistersStrategyInterface::readDnaRegister(dna) != mDrmApi_NO_ERROR) return;
  file << registerName("DNA") << std::endl;
  file << registerValue(dna, "DNA") << std::endl;
}

/** printSaasChallenge
*   \brief Display the value of the saas challenge.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printSaasChallengeHwReport(std::ostream &file) const {
  std::string saasChallenge;
  if (DrmControllerRegistersStrategyInterface::readSaasChallengeRegister(saasChallenge) != mDrmApi_NO_ERROR) return;
  file << registerName("SAAS CHALLENGE") << std::endl;
  file << registerValue(saasChallenge, "SAAS CHALLENGE") << std::endl;
}

/** printLicenseTimerCounter
*   \brief Display the value of the license timer counter.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printLicenseTimerCounterHwReport(std::ostream &file) const { }

/** printLogs
*   \brief Display the value of the logs register.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printLogsHwReport(std::ostream &file) const {
  unsigned int numberOfDetectedIps;
  std::string logs;
  if (readNumberOfDetectedIpsStatusRegister(numberOfDetectedIps) != mDrmApi_NO_ERROR) return;
  if (DrmControllerRegistersStrategyInterface::readLogsRegister(numberOfDetectedIps, logs) != mDrmApi_NO_ERROR) return;
  file << registerName("LOGS") << std::endl;
  file << registerValue(concat("0b", logs), "LOGS") << std::endl;
}

/** printVlnvFile
*   \brief Display the value of the vlnv file.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printVlnvFileHwReport(std::ostream &file) const {
  unsigned int numberOfDetectedIps;
  std::vector<std::string> vlnvFile;
  if (readNumberOfDetectedIpsStatusRegister(numberOfDetectedIps) != mDrmApi_NO_ERROR) return;
  if (readVlnvFileRegister(numberOfDetectedIps, vlnvFile) != mDrmApi_NO_ERROR) return;
  file << fileName("VLNV") << std::endl;
  file << registerValue(vlnvFile, "VLNV", -1) << std::endl;
}

/** printLicenseFile
*   \brief Display the license file.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printLicenseFileHwReport(std::ostream &file) const {
  unsigned int numberOfDetectedIps;
  std::string licenseFile;
  unsigned int licenseFileSize = mLicenseFileHeaderWordNumber;
  if (readNumberOfDetectedIpsStatusRegister(numberOfDetectedIps) != mDrmApi_NO_ERROR) return;
  licenseFileSize += numberOfDetectedIps*mLicenseFileIpBlockWordNumber;
  if (readLicenseFileRegister(licenseFileSize, licenseFile) != mDrmApi_NO_ERROR) return;
  file << fileName("LICENSE") << std::endl;
  file << registerValue(licenseFile, "LICENSE WORD", (DRM_CONTROLLER_SYSTEM_BUS_DATA_SIZE/DRM_CONTROLLER_NIBBLE_SIZE)*mLicenseWordRegisterWordNumber, 0) << std::endl;
}

/** printTraceFile
*   \brief Display the trace file.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printTraceFileHwReport(std::ostream &file) const {
  unsigned int numberOfDetectedIps;
  std::vector<std::string> traceFile;
  if (readNumberOfDetectedIpsStatusRegister(numberOfDetectedIps) != mDrmApi_NO_ERROR) return;
  if (readTraceFileRegister(numberOfDetectedIps, traceFile) != mDrmApi_NO_ERROR) return;
  // the number of digits to show the ip index
  std::ostringstream writter;
  writter << numberOfDetectedIps-1;
  const unsigned int digits = writter.str().size();
  file << fileName("TRACE") << std::endl;
  for (unsigned int ii = 0; ii < numberOfDetectedIps; ii++) {
    // get the trace part for the current ip
    std::vector<std::string> currentTraceFile(traceFile.begin()+ii*mNumberOfTracesPerIp, traceFile.begin()+(ii+1)*mNumberOfTracesPerIp);
    file << registerValue(currentTraceFile, concat(wsConcat("IP", padRight('0', digits, (int)ii)), " - Trace "), 0) << std::endl;
  }
}

/** printMailBoxFile
*   \brief Display the value of the mailbox file.
*   \param[in] file is the stream to use for the data print.
**/
void DrmControllerRegistersStrategy_v3_0_0::printMailBoxFileHwReport(std::ostream &file) const { }
