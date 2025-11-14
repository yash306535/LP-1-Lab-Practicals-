import time
import board
import adafruit_dht

dhtDevice = adafruit_dht.DHT11(board.D4)

while True:
    try:
        temperature_c = dhtDevice.temperature
        humidity = dhtDevice.humidity
        print(f"Temperature: {temperature_c}°C   Humidity: {humidity}%")
    except RuntimeError as error:
        print(f"Reading error: {error.args[0]}")
        time.sleep(2.0)
        continue
    except Exception as error:
        dhtDevice.exit()
        raise error
    time.sleep(3.0)
