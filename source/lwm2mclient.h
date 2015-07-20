#ifndef __LWM2MCLIENT_H__
#define __LWM2MCLIENT_H__

#include "lwm2m-client/m2minterfaceobserver.h"
#include "mbed/DigitalOut.h"

class M2MDevice;
class M2MSecurity;
class M2MObject;

class LWM2MClient : public M2MInterfaceObserver {
public:
    LWM2MClient();

    ~LWM2MClient();

    bool create_interface();

    bool register_successful();

    bool unregister_successful();

    bool registration_update_successful();

    M2MSecurity* create_register_object();

    M2MDevice* create_device_object();

    void execute_function(void *argument);

    M2MObject* create_generic_object();

    void update_resource();

    void test_register(M2MObjectList object_list);

    void set_register_object(M2MSecurity *&register_object);

    void test_unregister();

    //Callback from mbed client stack when the bootstrap
    // is successful, it returns the mbed Device Server object
    // which will be used for registering the resources to
    // mbed Device server.
    void bootstrap_done(M2MSecurity *server_object);

    //Callback from mbed client stack when the registration
    // is successful, it returns the mbed Device Server object
    // to which the resources are registered and registered objects.
    void object_registered(M2MSecurity */*security_object*/, const M2MServer &/*server_object*/);

    //Callback from mbed client stack when the unregistration
    // is successful, it returns the mbed Device Server object
    // to which the resources were unregistered.
    void object_unregistered(M2MSecurity */*server_object*/);

    void registration_updated(M2MSecurity */*security_object*/, const M2MServer & /*server_object*/);

    //Callback from mbed client stack if any error is encountered
    // during any of the LWM2M operations. Error type is passed in
    // the callback.
    void error(M2MInterface::Error error);

    //Callback from mbed client stack if any value has changed
    // during PUT operation. Object and its type is passed in
    // the callback.
    void value_updated(M2MBase *base, M2MBase::BaseType type);

private:

    DigitalOut          _led;
    M2MInterface        *_interface;
    M2MSecurity         *_register_security;
    M2MDevice           *_device;
    M2MObject           *_object;
    bool                _error;
    bool                _registered;
    bool                _unregistered;
    bool                _registration_updated;
    int                 _value;
};
#endif //__LWM2MCLIENT_H__