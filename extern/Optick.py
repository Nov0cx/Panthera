import Utils
import os
from pathlib import Path
import subprocess

class OptickDownloader:
    version = "1.4.0"
    install = f"https://github.com/bombomby/optick/releases/download/{version}.0/Optick_{version}.zip"
    dist_dir = ""

    def check(self):
        print("Checking Optick...")
        self.dist_dir = Path.home() / "optick"
        has_optick = os.environ.get("OPTICK") is not None
        if not has_optick:
            print("Optick not found.")
            self.download()
        else:
            print("Optick found.")

    def download(self):
        print("Creating Optick directory...")
        if not os.path.exists(self.dist_dir):
            os.mkdir(self.dist_dir)
        print("Downloading Optick...")
        print(f"Downloading {self.install} to {self.dist_dir}")
        file = self.dist_dir / f"Optick_{self.version}.zip"
        Utils.DownloadFile(self.install, file)
        print("Extracting Optick...")
        Utils.UnzipFile(file)
        print("Optick downloaded and extracted.")
        print("Setting environment variables...")
        if os.name == 'posix':
            var1 = "export OPTICK=" + str(self.dist_dir)
            var2 = "export PATH=$PATH:" + str(self.dist_dir)
            subprocess.call(["bash", "-c", var1])
            subprocess.call(["bash", "-c", var2])
        if os.name == 'nt':
            var1 = "setx OPTICK " + str(self.dist_dir)
            subprocess.Popen(var1, shell=True).wait()

        print("Done.")

if __name__ == "__main__":
    downloader = OptickDownloader()
    downloader.check()