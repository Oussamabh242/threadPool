import asyncio
import sys

HOST = "127.0.0.1"
PORT = 65432
MAX_MESSAGE_LENGTH = 100
MAX_FILE_LENGTH = 20
CONCURRENT_REQUESTS = int(sys.argv[1])

async def tcp_client(client_id):
    try:
        reader, writer = await asyncio.open_connection(HOST, PORT)
        message = f"queue.h"
        padded_message = message.ljust(MAX_MESSAGE_LENGTH, '\0').encode('utf-8')

        writer.write(padded_message)
        await writer.drain()
        data = await reader.read(MAX_FILE_LENGTH)
        received_message = data.rstrip(b'\0').decode('utf-8' , errors='replace')
        print(f"Client {client_id} received: {received_message}")
        
        writer.close()
        await writer.wait_closed()
            
    except ConnectionRefusedError:
        print(f"Client {client_id}: Connection to {HOST}:{PORT} refused. Is the server running?")
    except Exception as e:
        print(f"Client {client_id}: An error occurred: {e}")

async def main():
    tasks = [tcp_client(i) for i in range(CONCURRENT_REQUESTS)]
    await asyncio.gather(*tasks)

if __name__ == "__main__":
    asyncio.run(main())
