import json

from django.shortcuts import render

# Create your views here.
from django.http import JsonResponse
from django.db.models import Avg, Count, OuterRef, Subquery, Q, Case, When, \
    IntegerField, Exists
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import get_object_or_404
from django.http import JsonResponse
from .models import Country,HostCity,Venue,Edition,Artist,Song,Ids
from .serializers import CountrySerializer,CountryDetailsSerializer,VenueSerializer,HostCitySerializer,HostCityDetailsSerializer,VenueDetailsSerializer,EditionSerializer,EditionDetailsSerializer,ArtistSerializer,ArtistDetailsSerializer,SongSerializer,SongDetailsSerializer,IdsSerializer,EditionSerializerAVG,SongArtistSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status,generics
from rest_framework.views import APIView

class CountryList(generics.ListCreateAPIView):
    queryset = Country.objects.all()
    serializer_class = CountrySerializer


class CountryDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Country.objects.all()
    serializer_class = CountryDetailsSerializer


class CountryFilter(generics.ListCreateAPIView):
    serializer_class = CountrySerializer

    def get_queryset(self):
        queryset = Country.objects.all()
        var = self.request.GET.get('var', 0)
        if var is not None:
            queryset = queryset.filter(quality_factor__gt=var)
        return queryset

#  http://127.0.0.1:8000/eurovision/filter/?var=400


class HostCityList(generics.ListCreateAPIView):
    queryset = HostCity.objects.all()
    serializer_class = HostCitySerializer

class HostCityDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = HostCity.objects.all()
    serializer_class = HostCityDetailsSerializer


class VenueList(generics.ListCreateAPIView):
    queryset = Venue.objects.all()
    serializer_class = VenueSerializer


class VenueDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Venue.objects.all()
    serializer_class = VenueDetailsSerializer

class EditionList(generics.ListCreateAPIView):
    queryset = Edition.objects.all()
    serializer_class = EditionSerializer

class EditionDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Edition.objects.all()
    serializer_class = EditionDetailsSerializer

class ArtistList(generics.ListCreateAPIView):
    queryset = Artist.objects.all()
    serializer_class = ArtistSerializer

class ArtistDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Artist.objects.all()
    serializer_class = ArtistDetailsSerializer

class SongList(generics.ListCreateAPIView):
    queryset = Song.objects.all()
    serializer_class = SongSerializer

class SongDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Song.objects.all()
    serializer_class = SongDetailsSerializer

class ArtistGetView(generics.ListCreateAPIView):
    queryset = Song.objects.all()
    serializer_class = SongArtistSerializer

class ArtistPostView(generics.RetrieveUpdateDestroyAPIView):
    queryset = Song.objects.all()
    serializer_class = SongArtistSerializer


class IdsList(generics.ListCreateAPIView):
    queryset = Ids.objects.all()
    serializer_class = IdsSerializer

class IdsDetailsList(generics.RetrieveUpdateDestroyAPIView):
    queryset = Ids.objects.all()
    serializer_class = IdsSerializer

class CountryIdsList(generics.ListCreateAPIView):
    queryset = Country.objects.all()
    serializer_class = IdsSerializer

class CountryIdsDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Country.objects.all()
    serializer_class = IdsSerializer


class EditionIdsList(generics.ListCreateAPIView):
    queryset = Ids.objects.all()
    serializer_class = IdsSerializer

class EditionIdsDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Ids.objects.all()
    serializer_class = IdsSerializer

class SongIdsList(generics.ListCreateAPIView):
    queryset = Song.objects.all()
    serializer_class = IdsSerializer

class SongIdsDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Song.objects.all()
    serializer_class = IdsSerializer

class EditionByCountryQF(generics.ListAPIView):

    serializer_class = EditionSerializerAVG

    def get_queryset(self):
        queryset = Edition.objects \
            .annotate(avg_qf=Avg('ids__country__quality_factor')) \
            .order_by('-avg_qf')
        return queryset


class EditionByCountryNR(generics.ListAPIView):
    serializer_class = EditionSerializer
    def get_queryset(self):
        queryset = Edition.objects \
            .annotate(country_nr=Count('countries__id')) \
            .order_by('-country_nr')
        return queryset

class SongArtistEndpoint(APIView):
    def post(self, request, pk):
        serializer = SongArtistSerializer(data=request.data, many=True)
        artist = get_object_or_404(Artist, id=pk)
        serializer.context['artist_id'] = artist
        if serializer.is_valid():
            serializer.save(artist_id=artist, using='')
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_204_NO_CONTENT)