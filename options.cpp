#include "options.h"

Options *Options::_options = 0;

Options *Options::instance()
{
    if(_options == 0){
        _options = new Options;
    }
    return _options;
}

Options::Options()
{

}
