/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.cpp,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/08 14:14:59 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
# include <io.h>
# include <direct.h>
# define stat _stat
# define S_IFREG _S_IFREG
# define S_IFDIR _S_IFDIR
# define access _access
# define mkdir _mkdir
# define rmdir _rmdir
#else
# include <dirent.h>
# include <unistd.h>
#endif // WIN32

#include "copasi.h"

#include "CDirEntry.h"
#include "utility.h"
#include "CCopasiMessage.h"

#include "randomGenerator/CRandom.h"

#ifdef WIN32
const std::string CDirEntry::Separator = "\\";
#else
const std::string CDirEntry::Separator = "/";
#endif

bool CDirEntry::isFile(const std::string & path)
{
  struct stat st;
  if (stat(utf8ToLocale(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG);
#else
  return S_ISREG(st.st_mode);
#endif
}

bool CDirEntry::isDir(const std::string & path)
{
  struct stat st;
  if (stat(utf8ToLocale(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return S_ISDIR(st.st_mode);
#endif
}

bool CDirEntry::exist(const std::string & path)
{
  struct stat st;
  if (stat(utf8ToLocale(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG ||
          (st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode));
#endif
}

bool CDirEntry::isReadable(const std::string & path)
{return (access(utf8ToLocale(path).c_str(), 0x4) == 0);}

bool CDirEntry::isWritable(const std::string & path)
{return (access(utf8ToLocale(path).c_str(), 0x2) == 0);}

std::string CDirEntry::baseName(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.
  if (start == std::string::npos)
    start = path.find_last_of("/");
#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  std::string::size_type end = path.find_last_of(".");
  if (end == std::string::npos || end < start)
    end = path.length();

  return path.substr(start, end - start);
}

std::string CDirEntry::fileName(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.
  if (start == std::string::npos)
    start = path.find_last_of("/");
#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  return path.substr(start);
}

std::string CDirEntry::dirName(const std::string & path)
{
  if (path == "") return path;
#ifdef WIN32 // WIN32 also understands '/' as the separator.
  std::string::size_type end = path.find_last_of(Separator + "/");
#else
  std::string::size_type end = path.find_last_of(Separator);
#endif

  if (end == path.length() - 1)
    {
#ifdef WIN32 // WIN32 also understands '/' as the separator.
      end = path.find_last_of(Separator + "/", end);
#else
      end = path.find_last_of(Separator, end);
#endif
    }

  if (end == std::string::npos) return "";

  return path.substr(0, end);
}

std::string CDirEntry::suffix(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.
  if (start == std::string::npos)
    start = path.find_last_of("/");
#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  std::string::size_type end = path.find_last_of(".");
  if (end == std::string::npos || end < start)
    return "";
  else
    return path.substr(end);
}

bool CDirEntry::createDir(const std::string & dir,
                          const std::string & parent)
{
  std::string Dir;
  if (parent != "") Dir = parent + Separator;
  Dir += dir;

  // Check whether the directory already exists and is writable.
  if (isDir(Dir) && isWritable(Dir)) return true;

  // Check whether the parent directory exists and is writable.
  if (!isDir(parent) || !isWritable(parent)) return false;

#ifdef WIN32
  return (mkdir(utf8ToLocale(Dir).c_str()) == 0);
#else
  return (mkdir(utf8ToLocale(Dir).c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0);
#endif
}

std::string CDirEntry::createTmpName(const std::string & dir,
                                     const std::string & suffix)
{
  CRandom * pRandom = CRandom::createGenerator();

  std::string RandomName;

  do
    {
      RandomName = dir + Separator;
      unsigned C_INT32 Char;

      for (unsigned C_INT32 i = 0; i < 8; i++)
        {
          Char = pRandom->getRandomU(35);
          if (Char < 10)
            RandomName += '0' + Char;
          else
            RandomName += 'a' - 10 + Char;
        }

      RandomName += suffix;
    }
  while (exist(RandomName));

  return RandomName;
}

bool CDirEntry::move(const std::string & from,
                     const std::string & to)
{
  if (!isFile(from)) return false;

  std::string To = to;

  // Check whether To is a directory and append the
  // filename of from
  if (isDir(To))
    To += Separator + fileName(from);

  bool success =
    (rename(utf8ToLocale(from).c_str(), utf8ToLocale(To).c_str()) == 0);

  if (!success)
    {
      {
        std::ifstream in(utf8ToLocale(from).c_str());
        std::ofstream out(utf8ToLocale(To).c_str());

        out << in.rdbuf();

        success = out.good();
      }

      remove(from);
    }

  return success;
}

bool CDirEntry::remove(const std::string & path)
{
  if (isDir(path))
    return (rmdir(utf8ToLocale(path).c_str()) == 0);
  else if (isFile(path))
    return (::remove(utf8ToLocale(path).c_str()) == 0);

  return false;
}

bool CDirEntry::removeFiles(const std::string & pattern,
                            const std::string & path)
{
  bool success = true;
  std::vector< std::string > PatternList;

  PatternList = compilePattern(pattern);

#ifdef WIN32

  // We want the same pattern matching behaviour for all platforms.
  // Therefore, we do not use the MS provided one and list all files instead.
  std::string FilePattern = path + "\\*";

  // Open directory stream and try read info about first entry
  struct _finddata_t Entry;
  C_INT32 hList = _findfirst(utf8ToLocale(FilePattern).c_str(), &Entry);

  if (hList == -1) return success;

  do
    {
      if (match(localeToUtf8(Entry.name), PatternList))
        {
          if (Entry.attrib | _A_NORMAL)
            {
              if (::remove((utf8ToLocale(path + Separator) + Entry.name).c_str()) != 0) success = false;
            }
          else
            {
              if (rmdir((utf8ToLocale(path + Separator) + Entry.name).c_str()) != 0) success = false;
            }
        }
    }
  while (_findnext(hList, &Entry) == 0);

  _findclose(hList);

#else

  DIR * pDir = opendir(utf8ToLocale(path).c_str());
  if (!pDir) return false;

  struct dirent * pEntry;

  while ((pEntry = readdir(pDir)) != NULL)
    {
      if (match(localeToUtf8(pEntry->d_name), PatternList))
        {
          if (isDir(localeToUtf8(pEntry->d_name)))
            {
              if (rmdir((utf8ToLocale(path + Separator) + pEntry->d_name).c_str()) != 0)
                success = false;
            }
          else
            {
              if (::remove((utf8ToLocale(path + Separator) + pEntry->d_name).c_str()) != 0)
                success = false;
            }
        }
    }

  closedir(pDir);

#endif // WIN32

  return success;
}

std::vector< std::string > CDirEntry::compilePattern(const std::string & pattern)
{
  std::string::size_type pos = 0;
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  std::vector< std::string > PatternList;

  while (pos != std::string::npos)
    {
      start = pos;
      pos = pattern.find_first_of("*?", pos);

      end = std::min(pos, pattern.length());

      if (start != end)
        PatternList.push_back(pattern.substr(start, end - start));
      else
        {
          PatternList.push_back(pattern.substr(start, 1));
          pos++;
        }
    };

  return PatternList;
}

bool CDirEntry::match(const std::string & name,
                      const std::vector< std::string > & patternList)
{
  std::vector< std::string >::const_iterator it = patternList.begin();
  std::vector< std::string >::const_iterator end = patternList.end();
  std::string::size_type at = 0;
  std::string::size_type after = 0;

  bool Match = true;
  while (it != end && Match)
    Match = matchInternal(name, *it++, at, after);

  return Match;
}

bool CDirEntry::isRelativePath(const std::string & path)
{
#ifdef WIN32
  return path[1] != ':';
#else
  return path[0] != '/';
#endif
}

bool CDirEntry::makePathRelative(std::string & absolutePath,
                                 const std::string & relativeTo)
{
  if (isRelativePath(absolutePath) ||
      isRelativePath(relativeTo)) return false; // Nothing can be done.

  std:: string RelativeTo = relativeTo;
  if (isFile(RelativeTo)) RelativeTo = dirName(RelativeTo);

  if (!isDir(RelativeTo)) return false;

  unsigned C_INT32 i, imax = std::min(absolutePath.length(), RelativeTo.length());

  for (i = 0; i < imax; i++)
    if (absolutePath[i] != RelativeTo[i]) break;

#ifdef WIN32
  if (i == 0) return false; // A different drive letter we cannot do anything
#endif

  RelativeTo = RelativeTo.substr(i);

  std::string relativePath;
  while (RelativeTo != "")
    {
      relativePath += "../";
      RelativeTo = dirName(RelativeTo);
    }

  if (relativePath != "")
    absolutePath = relativePath + absolutePath.substr(i);
  else
    absolutePath = absolutePath.substr(i + 1);

#ifdef WIN32
  for (i = 0, imax = absolutePath.length(); i < imax; i++)
    if (absolutePath[i] == '\\') absolutePath[i] = '/';
#endif

  return true;
}

bool CDirEntry::makePathAbsolute(std::string & relativePath,
                                 const std::string & absoluteTo)
{
  if (!isRelativePath(relativePath) ||
      isRelativePath(absoluteTo)) return false; // Nothing can be done.

  std:: string AbsoluteTo = absoluteTo;
  if (isFile(AbsoluteTo)) AbsoluteTo = dirName(AbsoluteTo);

  if (!isDir(AbsoluteTo)) return false;

  while (!relativePath.compare(0, 2, ".."))
    {
      AbsoluteTo = dirName(AbsoluteTo);
      relativePath = relativePath.substr(3);
    }

  relativePath = AbsoluteTo + Separator + relativePath;

  return true;
}

bool CDirEntry::matchInternal(const std::string & name,
                              const std::string pattern,
                              std::string::size_type & at,
                              std::string::size_type & after)
{
  bool Match = true;

  switch (pattern[0])
    {
    case '*':
      if (at != std::string::npos)
        {
          after = at;
          at = std::string::npos;
        }
      break;

    case '?':
      if (at != std::string::npos)
        {
          ++at;
          Match = (name.length() >= at);
        }
      else
        {
          ++after;
          Match = (name.length() >= after);
        }
      break;

    default:
      if (at != std::string::npos)
        {
          Match = (name.compare(at, pattern.length(), pattern) == 0);
          at += pattern.length();
        }
      else
        {
          at = name.find(pattern, after);
          Match = (at != std::string::npos);
          at += pattern.length();
        }

      break;
    }

  return Match;
}
