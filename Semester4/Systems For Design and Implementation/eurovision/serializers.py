from rest_framework import serializers
from .models import Country, HostCity, Venue, Edition, Song, Artist, Ids
from django.shortcuts import get_object_or_404

class CountrySerializer(serializers.ModelSerializer):
    class Meta:
        model = Country
        fields = ('id', 'country_name', 'year_of_entrance', 'country_capital', 'quality_factor')


class HostCitySerializer(serializers.ModelSerializer):
    class Meta:
        model = HostCity
        fields = ('__all__')


class VenueSerializer(serializers.ModelSerializer):
    class Meta:
        model = Venue
        fields = ('__all__')


class EditionSerializer(serializers.ModelSerializer):
    country_nr = serializers.IntegerField(read_only=True)
    class Meta:
        model = Edition
        fields = ('id', 'edition_year', 'final_date', 'motto', 'venue_id', 'country_nr')


class EditionSerializerAVG(serializers.ModelSerializer):
    avg_qf = serializers.FloatField(read_only=True)

    class Meta:
        model = Edition
        fields = ('id', 'edition_year', 'final_date', 'motto', 'venue_id', 'avg_qf')


class EditionDetailsSerializer(serializers.ModelSerializer):
    venue_id = VenueSerializer(read_only=True)
    countries = CountrySerializer(read_only=True, many=True)

    class Meta:
        model = Edition
        fields = ('id', 'edition_year', 'final_date', 'motto', 'venue_id', 'countries')


class VenueDetailsSerializer(serializers.ModelSerializer):
    host_city_id = HostCitySerializer(read_only=True)
    editions = EditionSerializer(read_only=True, many=True)

    class Meta:
        model = Venue
        fields = ('id', 'venue_name', 'venue_adress', 'host_city_id', 'capacity', 'rating', 'editions')


class HostCityDetailsSerializer(serializers.ModelSerializer):
    venues = VenueSerializer(read_only=True, many=True)

    class Meta:
        model = HostCity
        fields = (
        'id', 'host_city_name', 'host_city_population', 'host_city_mayor', 'is_capital', 'quality_factor', 'venues')


class ArtistSerializer(serializers.ModelSerializer):
    class Meta:
        model = Artist
        fields = ('id', 'artist_name', 'artist_age', 'country')


class SongSerializer(serializers.ModelSerializer):
    class Meta:
        model = Song
        fields = ('id', 'song_name', 'artist_id', 'release_date', 'album_name')


class SongDetailsSerializer(serializers.ModelSerializer):
    artist_id = ArtistSerializer(read_only=True)

    def validate_edition_id(self, value):
        filter = Artist.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError("Artist does not exist")
        return value

    class Meta:
        model = Song
        fields = ('id', 'song_name', 'artist_id', 'release_date', 'album_name')


class ArtistDetailsSerializer(serializers.ModelSerializer):
    songs = SongSerializer(read_only=True, many=True)
    country = CountrySerializer(read_only=True)

    class Meta:
        model = Artist
        fields = ('id', 'artist_name', 'artist_age', 'songs', 'country')


class SongArtistSerializer(serializers.ModelSerializer):
    id = serializers.IntegerField()


    def create(self, validated_data):
        song_id = validated_data['id']
        song = get_object_or_404(Song, pk=song_id)
        song.artist_id = validated_data['artist_id']
        db = validated_data.get('using', None)
        song.save(using=db)
        return song

    class Meta:
        model = Song
        fields = ['id']


class IdsSerializer(serializers.ModelSerializer):
    edition_id = serializers.IntegerField()
    country_id = serializers.IntegerField()

    def validate_edition_id(self, value):
        filter = Edition.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError("Edition does not exist")
        return value

    def validate_country_id(self, value):
        filter = Country.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError("Country does not exist")
        return value

    class Meta:
        model = Ids
        fields = ('id', 'edition_id', 'country_id', 'place', 'points')


class CountryDetailsSerializer(serializers.ModelSerializer):
    editions = EditionSerializer(read_only=True, many=True)
    artists = ArtistSerializer(read_only=True, many=True)

    class Meta:
        model = Country
        fields = (
            'id', 'country_name', 'year_of_entrance', 'country_capital', 'quality_factor', 'artists', 'editions')

