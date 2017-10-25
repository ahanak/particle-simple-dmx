/* SimpleDmx library by André Hanak <impressum@a-hanak.de>
 */

#include "SimpleDmx.h"

/**
 * Constructor.
 */
SimpleDmx::SimpleDmx()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void SimpleDmx::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void SimpleDmx::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void SimpleDmx::doit()
{
    Serial.println("called doit");
}
