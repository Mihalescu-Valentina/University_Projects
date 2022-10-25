from src.repository.taxi_repo import TaxiRepository
from src.service.taxi_service import TaxiService
from src.ui.start import Console

if __name__ == '__main__':
    repo = TaxiRepository()
    service = TaxiService(repo)
    console = Console(service)
    console.run()