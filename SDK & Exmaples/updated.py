# coding: utf-8
import os
from shutil import copyfile

def get_files(current_path='./'):
    all_path = []
    for fpath,dirs,fs in os.walk(current_path):   # os.walk是获取所有的目录
        for f in fs:
            path = os.path.join(fpath,f)
            all_path.append(path)
    return all_path
    
def replace_files(source_files, replace_files):
    source_path = get_files(source_files)
    replace_path = get_files(replace_files)

    try:
        for sp in source_path:
            print("*** ", sp)
            for rp in replace_path:
                a, b = os.path.split(sp)
                c, d = os.path.split(rp)
                if b == d:
                    print("--> ",rp)
                    copyfile(sp, rp)
    except IOError as e:
       print("Unable to copy file. %s" % e)
       os.system('pause')
    except:
       print("Unexpected error:", sys.exc_info())
       os.system('pause')

if __name__ == "__main__":
    replace_files(".\\sdk\\api", ".\\examples")
    replace_files(".\\sdk\\libs\\msvc_x86", ".\\examples")
    print("\nDone\n")
    os.system('pause')


