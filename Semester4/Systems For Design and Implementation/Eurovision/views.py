from django.http import JsonResponse
from .models import Country
from .serializers import CountrySerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status

@api_view(['GET','POST'])
def CountryList(request):
    if request.method == 'GET':
        countries = Country.objects.all()
        serializer = CountrySerializer(countries,many = True)
        return Response(serializer.data)

    if request.method == 'POST': #add
        serializer = CountrySerializer(data = request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data,status = status.HTTP_201_CREATED)

@api_view(['GET','PUT','DELETE'])
def CountryDetail(request,id):

    try:
        country = Country.objects.get(pk=id)
    except Country.DoesNotExist:
        return Response(status = status.HTTP_404_NOT_FOUND)
    if(request.method == 'GET'):
        serializer = CountrySerializer(country)
        return Response(serializer.data)
    elif request.method == 'PUT': #update
        serializer = CountrySerializer(country,data = request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors,status = status.HTTP_400_BAD_REQUEST)

    elif request.method == 'DELETE':
        country.delete()
        return Response(status = status.HTTP_204_NO_CONTENT)

    #in CountryDetails use / at the end of the url in put and delete,not in get!!
