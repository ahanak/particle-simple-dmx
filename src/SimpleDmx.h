#pragma once

/* SimpleDmx library by André Hanak <impressum@a-hanak.de>
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

// This is your main class that users will import into their application
class SimpleDmx
{
public:
  /**
   * Constructor
   */
  SimpleDmx();

  /**
   * Example method
   */
  void begin();

  /**
   * Example method
   */
  void process();

private:
  /**
   * Example private method
   */
  void doit();
};
