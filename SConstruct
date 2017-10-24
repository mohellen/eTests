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
homedir = os.path.expenduser("~")
basedir = os.getcwd()
srcdir = basedir + "/src"
bindir = basedir + "/bin"
#########################

#### Customs command line variables ####
########################################
homedir = os.path.expenduser("~")
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
evn.Append( LD_LIBRARY_PATH=libpath )
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
# For every .cpp file in src
for cfile in 

# Specify build name

BuildName = env.get("EXEC")
# Save the base path
BASEPATH = os.getcwd()
BUILDPATH = BASEPATH + '/bin/' + BuildName + '_build'
TARGET = BASEPATH + '/bin/' + BuildName
# Make output and build dir
if not os.path.exists(BASEPATH + '/output'):
    os.makedirs(BASEPATH + '/output')
if not os.path.exists(BUILDPATH):
    os.makedirs(BUILDPATH)
# List of objects for the build
OBJ = []
# Build objects from sources file
# find each subdir in src            
for sdir in os.listdir('src'):
    srcdir = BASEPATH + '/src/' + sdir
    # confirm this is a dir (not a file), then
    if (os.path.isdir(srcdir)):
        # create the corresponding build path
        blddir = BUILDPATH + '/' + sdir
        if not os.path.exists(blddir):
            os.makedirs(blddir)
        # find all source files in this dir
        srcfiles = []
        for f in os.listdir('src/'+sdir):
            if (f.endswith('.cpp') or f.endswith('.c') or f.endswith('.cc')):
                # NOTE: Must prefix "build dir" to each source file in order 
                #       to be built in the build dir
                srcfiles += [blddir +'/'+ f]
                # Put the object file into object list
                OBJ += [ os.path.splitext(blddir +'/'+ f)[0]+'.o' ]
        # compile all files
        env.VariantDir(blddir, srcdir, duplicate=0)
        env.Object(srcfiles)
    # if sdir is indeed a file, check if it's a source file
    elif (sdir.endswith('.cpp') or sdir.endswith('.c') or sdir.endswith('.cc')):
        srcdir = BASEPATH + '/src'
        blddir = BUILDPATH
        srcfile = blddir +'/'+ sdir
        OBJ += [ os.path.splitext(blddir +'/'+ sdir)[0]+'.o' ]
        # compile the file
        env.VariantDir(blddir, srcdir, duplicate=0)
        env.Object(srcfile)
# Build program
env.Program(TARGET, OBJ, LIBS=libs, LIBPATH=libpath)
########################################


############### CLEANUP ################
########################################
env.Clean("clean", [TARGET, BUILDPATH])
########################################

# TODO: make phony target 'scons sgpp' 

#sgpp:
#    mkdir -p $(BASEPATH)/lib; cd $(BASEPATH)/dep/sgpp-base-2.0.0; scons -c; scons BUILDDIR=$(BASEPATH)/lib -j4; cd $(BASEPATH)







