/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2015, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"
#include "../../Lib/TLibEncoder/ggPkg.h"

//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"
#include "../../Lib/TLibEncoder/ggPkg.h"


// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;
  nameFile = argv[9];

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );

   ofstream outfile;
   outfile.open((nameFile + ".txt").c_str(),ios::out);
   outfile.close();
  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

  // starting time
  Double dResult;
  clock_t lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);

  ofstream timeTabs,countTabs;
  timeTabs.open(("time_" + nameFile +  ".csv").c_str(),ios::out);
  countTabs.open(("count_" + nameFile +  ".csv").c_str(),ios::out);
  
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);
  
//  timeTabs << "Tempo;" << ((Double)(totalCount)) << endl;
//  timeTabs << "Tempo intra;" << ((Double)(intraCount)) << endl;
//  timeTabs << "Tempo intraCSC;" << ((Double)(intraCSCount)) << endl;
//  timeTabs << "Tempo intraPCM;" << ((Double)(intraPCMCount)) << endl;
//  timeTabs << "Tempo inter;" << ((Double)(interCount)) << endl;
//  timeTabs << "Tempo intraBC;" << ((Double)(intraBCCount)) << endl;
//  timeTabs << "Tempo hash inter;" << ((Double)(HashInterCount)) << endl;
//  timeTabs << "Tempo palette;" <<((Double)(PalletMCount)) << endl;
    
  timeTabs << ((Double)(totalCount)) << ";" << ((Double)(intraCount)) << ";"  << ((Double)(interCount)) << ";" << ((Double)(intraBCCount)) << ";" << ((Double)(HashInterCount)) << ";" << ((Double)(PalletMCount));
  
  //timeTabs << endl;
  
//  countTabs << "Total CUs;" << totalCuCount << endl;
//  countTabs << "Intra CUs;" << intraCuCount << endl;
//  countTabs << "IntraBC CUs;" << ibcCuCount << endl;
//  countTabs << "Palette CUs;" << pltCuCount << endl;
//  countTabs << "Skip CUs;" << skipCount << endl;
//  countTabs << "??? CUs;" << unIdCount << endl;
  
  countTabs << totalCuCount << ";" << intraCuCount << ";" << ibcCuCount << ";" << pltCuCount << ";" << skipCount  << ";" << unIdCount;
  // destroy application encoder class
  
  // destroy application encoder class
  cTAppEncTop.destroy();

  return 0;
}

//! \}
