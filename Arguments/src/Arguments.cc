#include <Arguments/Arguments.h>

Arguments::Arguments() {
    //this->arg = new nlohmann::json();
}

Arguments::~Arguments() {
    //delete this->arg;
    this->cfg.clear();
}

void Arguments::set_argument(std::string arg, Arguments::argtype t) {
    this->it = this->cfg.find(arg);
    if( this->it == this->cfg.end() ) {
        this->cfg[arg] = t;
    }
}

nlohmann::json Arguments::parse(int argc, char * argv[] ) {
    for( int index = 1; index < argc; ++index ) {
        std::string parg = argv[index];

        this->it = this->cfg.find(parg);
        parg = parg.substr(2, parg.size() - 2);

        if( this->it != this->cfg.end() ) {
            switch( this->it->second ) {
                case Arguments::boolean:
                    this->arg[parg] = true;
                    break;
                case Arguments::integer:
                    if( index + 1 < argc ) {
                        index += 1;
                        std::string int_arg = argv[index];
                        std::stringstream conv_int(int_arg);
                        int s_int = 0;
                        conv_int >> s_int;

                        this->arg[parg] = s_int;
                    }
                    break;
                case Arguments::string:
                    if( index + 1 < argc ) {
                        index += 1;
                        std::string next = argv[index];
                        this->arg[parg] = next;
                    }
                    break;
            }
        }
    }

    return this->arg;
}