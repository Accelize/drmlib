/*
Copyright (C) 2018, Accelize

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <fstream>

#include "log.h"

namespace Accelize {
    namespace DRM {

        eLogLevel sLogVerbosity = eLogLevel::ERROR;
        eLogFormat sLogFormat = eLogFormat::SHORT;
        std::string sLogFilePath = std::string("");
        //std::unique_ptr<std::ostream> sLogStream;
        //std::ostream* sLogStream = nullptr;
        std::ostream* sLogStream = &std::cout;


        void initLog() {
            /*
            std::lock_guard<std::recursive_mutex> lock(mLogMutex);
            if ( sLogFilePath.size() ) {
                //std::unique_ptr<std::ofstream> ofs( new std::ofstream( sLogFilePath ) );
                std::ofstream* ofs = new std::ofstream( sLogFilePath );
                if (!ofs->is_open()) {
                    Throw(DRM_ExternFail, "Unable to access file: ", sLogFilePath);
                }
                //sLogStream = std::move(ofs);
                sLogStream = ofs;
                Debug( "Init logger to file ", sLogFilePath );
                //sLogStream = std::unique_ptr<std::ostream>(&std::cout);
            }
            else {
                //sLogStream = std::unique_ptr<std::ostream>(&std::cout);
                sLogStream = &std::cout;
                Debug( "Init logger to stdout" );
            }*/
        }

        void uninitLog() {
            /*
            Debug( "Uninit logger" );
            if ( sLogFilePath.size() ) {
                std::lock_guard<std::recursive_mutex> lock(mLogMutex);
                //sLogStream.release();
                delete sLogStream;
                sLogStream = nullptr;
            }*/
        }
    }
}
