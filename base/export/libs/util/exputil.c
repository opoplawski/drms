#include "jsoc.h"
#include "exputil.h"
#include "drms_keyword.h"

/* File name generator used for exports from DRMS.
 * Takes a segment pointer and filename template.
 * Returns generated filename.
 *
 * Template rules:
 * Any char not enclosed in '{}' is used explicitly.
 * The first word, up to an optional ':' must be one of the
 * special proxy names or a keyword from the record associated
 * with the provided segment.
 * For keywords, #, and recnum, a display format may be provided after a ':'.
 * The special proxy keyword names are:
 *   seriesname which returns the seriesname
 *   segment which returns the segment filename
 *   recnum which returns the record number.
 *   # which returns the ordinal number of the filename generated within this run of the calling program.
 * The optional display format is a 'printf' style format.
 * The default format for recnum is '%lld'
 * The default format for # is '%05d'
 * The default format for all keywords is the JSD display format for that keyword.
 * Times allow both precision and zone specifiers in the display format.
 * The two allowed quantities, precision and zone are separated with a comma, ','
 * Both time quantities are optional with precision defaulting to 0 and zone to the JSD value.
 * The precision is an integer following the rules for sprint_time.
 * Thus a positive precision is the number of digits of fractional seconds.
 * and a negative precision denotes how many fields to omit from the right.
 * A -1 omits seconds, -2 minutes, etc.
 * A special modification letter may preceed the precision.
 * At present the only options are 'A' for 'alternate' format
 * and 'D' for directory format.  'A' casues the time component separators '.' and ':' to be omitted.
 * 'D' does the same but surrounds the 3 date fields with '@' chars.
 * The names made with the 'D' can be easily scripted to mode the export files
 * into date based directory trees.
 * Thus a time keyword of T_REC for mdi.fd_M of {T_REC:A-1} would make
 * a filename component of '19960624_1230_TAI'
 *
 */

ExpUtlStat_t exputl_mk_expfilename(DRMS_Segment_t *seg, 
                                   const char *filenamefmt, 
                                   char *filename)
{
   static int namesMade = 0;
   ExpUtlStat_t ret = kExpUtlStat_Success;
   char *fn = filename;
   char format[1024];
   char *fmt;
   if (filenamefmt)
     snprintf(format, sizeof(format), "%s", filenamefmt);
   else
     snprintf(format, sizeof(format), "{seriesname}.{recnum:%%lld}.{segment}");
   fmt = format;
   *fn = '\0';
   while (*fmt)
      {
      char *last;
      if (*fmt == '{')
         {
         char *val;
         char *p;
         char *keyname;
         char *layout;
         last = index(fmt, '}');
         if (!last)
            {
            ret = kExpUtlStat_InvalidFmt;
            break;
            }

         keyname = ++fmt;
         layout = NULL;
         *last = '\0';
         for (p=keyname; p<last; p++)
            {
            if (*p == ':')
               {
               *p++ = '\0';
               layout = p;
               }
            }
         if (*keyname)
            {
            char valstr[128];
            if (strcmp(keyname, "#") == 0) // insert record count within current program run
               {
               snprintf(valstr, sizeof(valstr), (layout ? layout : "%05d"), namesMade++);
               val = valstr;
               }
            else if (strcmp(keyname,"seriesname")==0)
               val = seg->record->seriesinfo->seriesname;
            else if (strcmp(keyname,"recnum")==0)
               {
               snprintf(valstr, sizeof(valstr), (layout ? layout : "%lld"), 
                        seg->record->recnum); 
               val = valstr;
               }
            else if (strcmp(keyname,"segment")==0)
               val = seg->filename;
            // At this point the keyname is a normal keyword name.
            else if (layout) // use user provided format to print keyword.  User must be careful.
              {
              DRMS_Keyword_t *key = drms_keyword_lookup(seg->record,keyname,1);
              if (key->info->type == DRMS_TYPE_TIME)
                { // do special time formats here 
                char formatwas[DRMS_MAXFORMATLEN], unitwas[DRMS_MAXUNITLEN];
                int precision = 0;
                char Mod = ' ';
                strncpy(formatwas, key->info->format, DRMS_MAXFORMATLEN);
                strncpy(unitwas, key->info->unit, DRMS_MAXUNITLEN);
                if (isalpha(*layout)) Mod = *layout++;
                if (isdigit(*layout) || *layout == '-')
                  precision = strtol(layout, &layout, 10);
                snprintf(key->info->format, DRMS_MAXFORMATLEN, "%d", precision);
                if (*layout == ',' && *(layout+1))
                  strncpy(key->info->unit,layout+1,DRMS_MAXUNITLEN);
                val = drms_getkey_string(seg->record,keyname,NULL);
                strncpy(key->info->format, formatwas, DRMS_MAXFORMATLEN);
                strncpy(key->info->unit, unitwas, DRMS_MAXUNITLEN);
                if (Mod != ' ')
                   { 
                   if (Mod == 'A')
                     {
                     int i;
                     char *cp;
                     for (i=0, cp=val; *cp; cp++)
                       if (*cp != '.' && *cp != ':')
                         valstr[i++] = *cp;
                     valstr[i] = '\0';
                     val = valstr;
                     }
                   else if (Mod == 'D')
                     {
                     int i;
                     char *cp;
                     valstr[0] = '@';
                     for (i=1, cp=val; *cp; cp++)
                       {
                       if (*cp == ':') continue;
                       if (*cp == '.' || i == 11)
                         valstr[i++] = '@';
                       else
                         valstr[i++] = *cp;
                       }
                     valstr[i] = '\0';
                     val = valstr;
                     }
                   // else ignore unrecognized Mod char
                   }
                else
                  {
                  strncpy(valstr, val, 128);
                  // free(val);
                  val = valstr;
                  }
                }
              else
                {
                char formatwas[DRMS_MAXFORMATLEN];
                strncpy(formatwas, key->info->format, DRMS_MAXFORMATLEN);
                strncpy(key->info->format,layout,DRMS_MAXFORMATLEN);
                val = drms_getkey_string(seg->record,keyname,NULL);
                strncpy(key->info->format, formatwas, DRMS_MAXFORMATLEN);
                // free(val);
                val = valstr;
                }
              }
            else // No user provided layout string
              val = drms_getkey_string(seg->record,keyname,NULL);
            if (!val)
               {
               ret = kExpUtlStat_InvalidFmt;
               val = "ERROR";
               }
            else
               {
               strncpy(valstr, val, 128);
               // free(val);
               val = valstr;
               }
            for (p=val; *p; )
               {
               *fn++ = *p++;
               }
            *fn = '\0';
            }
         fmt = last+1;
         }
      else
        *fn++ = *fmt++;
      }
   *fn = '\0';

   return ret;
}
