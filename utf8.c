/* ----------------------------------------------------------------- */
/*  CODE FOR PARSING INDIAN LANGUAGES				               */
/*           developed by Indian Language Text-to-Speech Consortium  */
/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2015  Indian Language Text-to-Speech Consortium    */
/*                      Headed by Prof Hema A Murthy, IIT Madras     */
/*                      Department of Computer Science & Engineering */
/*                      hema@cse.iitm.ac.in                          */
/*                                                                   */
/*                                 				               */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - It can be used for research purpose but for commercial use,     */
/*   prior permission is needed.                                     */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the Indian Language TTS Consortium nor      */
/*   the names of its contributors may be used to endorse or promote */
/*   products derived from this software without specific prior      */
/*   written permission.					               */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

/* ########################### Author Info ######################### */
/*		Name:	Arun Baby
/*  		Orgn: IIT Madras
/*    	Email: arunbaby0@gmail.com
/*		Date:	01-01-2016
/*		Desc:	UTF-8 Handler for unifed parser
/* ########################### Author Info END ##################### */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utf8.h"

char *Utf8Replace(char *needle, char *replace, char *haystack)
{
	size_t replaceLength = strlen(replace), needleLength = strlen(needle), len = strlen(haystack);
	int32_t diff = (int32_t)(replaceLength - needleLength);
	char *newString = calloc((len + diff + 1), sizeof(char));
	char *pos = strstr(haystack, needle);
	if (pos == NULL)
	{
		strcpy(newString, haystack);
		return newString;
	}
	size_t numberOfShifts = pos - haystack;
	memcpy(newString, haystack, numberOfShifts);																 // Add begining of the string
	memcpy(newString + numberOfShifts, replace, replaceLength);													 // Copy the replacement in place of the needle
	memcpy(newString + numberOfShifts + replaceLength, pos + needleLength, len - numberOfShifts - needleLength); // Copy the remainder of the initial string
	return newString;
}
char *Utf8ReplaceAll(char *needle, char *replace, char *haystack)
{
	char *newString = Utf8Replace(needle, replace, haystack), *oldString = NULL;
	if (strstr(newString, needle) == NULL)
	{
		return newString;
	}
	while (strstr(newString, needle) != NULL)
	{
		oldString = newString;
		newString = Utf8Replace(needle, replace, newString);
		free(oldString);
	}
	return newString;
}
