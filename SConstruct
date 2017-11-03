import os
import shutil
import SCons

###### Ininitialize env virables #######
########################################
cxx = 'mpicxx'
# Compile flags
cppflags = ['-O3','-std=c++11']
# Include paths: -Iinclude without '-I'
cpppath = []
# Library look up paths: -Lpath without '-L'
libpath = []
# Libraries to link: -lmylib without '-l'
libs = ['mpi','mpicxx']
########################################

#### Local variables ####
#########################
homedir = os.path.expanduser("~")
basedir = os.getcwd()
srcdir = basedir + "/src"
bindir = basedir + "/bin"
#########################

#### Customs command line variables ####
########################################
vars = Variables()
vars.Add("impifreq", "Set iMPI adaptation frequency (defalt: 120)", 120)
vars.Add("impipath", "Set iMPI install path", homedir + "/workspace/ihpc-install")
########################################


########## Setup environment ###########
########################################
env = Environment(variables=vars, ENV=os.environ)
impifreq = env.get("impifreq")
impipath = env.get("impipath")

cpppath += [impipath + '/include']
libpath += [impipath + '/lib']

env.Replace( CXX=cxx )
env.Append( CPPPATH=cpppath )
env.Append( LD_LIBRARY_PATH=libpath )
env.Append( CPPFLAGS=cppflags )
env.Append( CPPDEFINES=['IMPI_FREQ=' + str(impifreq)] )
########################################


############ Help Message ##############
########################################
env.Help("""
Usage: 
To build with defalt options: scons
To build with special options: scons <OPTION>=<VALUE>
To clean up build: scons -c

Available options are:
"""+vars.GenerateHelpText(env)
)
########################################


################ BUILD #################
########################################
# Make build dir
if not os.path.exists(bindir):
    os.makedirs(bindir)
# find each source file in src
for ss in os.listdir('src'):
    pathss = srcdir + '/' + ss
    # confirm this is a file and it's a source file
    if ( os.path.isfile(pathss) and (ss.endswith('.cpp') or ss.endswith('.c') or ss.endswith('.cc')) ):
		TARGET = bindir + '/' + os.path.splitext(ss)[0]
		# Build program
		env.Program(TARGET, [pathss], LIBS=libs, LIBPATH=libpath)
########################################


############### CLEANUP ################
########################################
env.Clean("clean", [bindir])
########################################


