import subprocess

for i in range(0, 21):
    process = subprocess.Popen(["curl http://challenge01.root-me.org:54017/"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

out, _ = process.communicate()
print(str(out))
