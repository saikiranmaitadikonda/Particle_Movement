//
//  ElementException.cpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 05/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#include "ElementException.hpp"

using std::cout;
using std::endl;
using std::cerr;

namespace ParticleMotion {
    
    template <typename T>
    void ElementException::buildException (const T& e)
    {
        
        auto errorCode = e.code();
        cerr << "- Exception Category: "      << errorCode.category().name() << endl;
        cerr << "- Exception Value: "         << errorCode.value() << endl;
        cerr << "- Exception Message: "       << errorCode.message() << endl;
        cerr << "- Default Category: "        << errorCode.default_error_condition().category().name() << endl;
        cerr << "- Default Value: "           << errorCode.default_error_condition().value() << endl;
        cerr << "- Default Message: "         << errorCode.default_error_condition().message() << endl;
    }
    
    void ElementException::printException()
    {
        try {
            throw; //Rethrow exception
        } catch (const std::runtime_error& e) {
            cerr << "RUNTIME EXCEPTION: " << e.what() << endl;
        } catch (const std::ios_base::failure& e) {
            cerr << "I/O EXCEPTION: " << e.what() << endl;
            buildException(e);
        } catch (const std::system_error& e) {
            cerr << "SYSTEM ERROR EXCEPTION: " << e.what() << endl;
            buildException(e);
        } catch (const std::future_error& e) {
            cerr << "FUTURE ERROR EXCEPTION: " << e.what() << endl;
            buildException(e);
        } catch (const std::bad_alloc& e) {
            cerr << "BAD ALLOC EXCEPTION: " << e.what() << endl;
        } catch (const std::exception& e) {
            cerr << "EXCEPTION: " << e.what() << endl;
        } catch (...) {
            cerr << "UNKNOWN EXCEPTION" << endl;
        }
    }
}