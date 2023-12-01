FROM python3:latest
LABEL Maintener="calculator"
WORKDIR /home/geoffrey/Documents/B2_reseau/Tp5/Docker
COPY /home/geoffrey/Documents/B2_reseau/Tp5/Scripts/server.py .
CMD ["python3", "server.py"]
