/**
*  \file      DrmControllerLicenseFileSizeException.hpp
*  \version   3.2.0.0
*  \date      December 2018
*  \brief     Class DrmControllerLicenseFileSizeException defines procedures
*             for license file size exceptions reporting, inherihts from std::exception.
*  \copyright Licensed under the Apache License, Version 2.0 (the "License");
*             you may not use this file except in compliance with the License.
*             You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*             Unless required by applicable law or agreed to in writing, software
*             distributed under the License is distributed on an "AS IS" BASIS,
*             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*             See the License for the specific language governing permissions and
*             limitations under the License.
**/

#ifndef __DRM_CONTROLLER_LICENSE_FILE_SIZE_EXCEPTION_HPP__
#define __DRM_CONTROLLER_LICENSE_FILE_SIZE_EXCEPTION_HPP__

#include <exception>
#include <string>

/**
*   \namespace DrmControllerLibrary
**/
namespace DrmControllerLibrary {

  /**
  *  \class     DrmControllerLicenseFileSizeException DrmControllerLicenseFileSizeException.hpp "include/DrmControllerLicenseFileSizeException.hpp"
  *  \brief     Class DrmControllerLicenseFileSizeException defines procedures
  *             for license file size exceptions reporting, inherihts from std::exception.
  **/
  class DrmControllerLicenseFileSizeException: public std::exception {

    // public members, functions ...
    public:

      /** DrmControllerLicenseFileSizeException
      *   \brief Class constructor. This method does not throw exception.
      *   \param[in] message is the error message.
      **/
      DrmControllerLicenseFileSizeException(const std::string &message = "Unknown exception.") throw()
        : mMessage(message) { }

      /** ~DrmControllerLicenseFileSizeException
      *   \brief Class destructor. This method does not throw exception.
      **/
      virtual ~DrmControllerLicenseFileSizeException() throw() { }

      /** what
      *   \brief Get the type of the error. This method does not throw exception.
      *   \return Returns the message related to the error.
      **/
      inline virtual const char* what() const throw() {
        return mMessage.c_str();
      }

    // protected members, functions ...
    protected:

    // private members, functions ...
    private:
      const std::string mMessage; /**<The value of the error message.**/

  }; // class DrmControllerLicenseFileSizeException

} // namespace DrmControllerLibrary

#endif // __DRM_CONTROLLER_LICENSE_FILE_SIZE_EXCEPTION_HPP__