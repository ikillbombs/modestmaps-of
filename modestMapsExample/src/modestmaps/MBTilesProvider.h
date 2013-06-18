#ifndef OPENSTREETMAPPROVIDER
#define OPENSTREETMAPPROVIDER

#include "AbstractMapProvider.h"
#include "MercatorProjection.h"

class MBTilesProvider : public AbstractMapProvider {
	
public:
	
	vector<string> subdomains;
	string serverName;
    
    // use Tilestream for streaming your tiles
    // Example for url server : tiles.subdomain.domain.com/v2/directory/
    
	MBTilesProvider(string _server):

		// this is the projection and transform you'll want for any Google-style map tile source:
		AbstractMapProvider(new MercatorProjection(26, Transformation(1.068070779e7, 0.0, 3.355443185e7, 0.0, -1.068070890e7, 3.355443057e7)))
	{
        
        serverName = _server;
		subdomains.push_back("");
	}
    
    
	
	int tileWidth() {
		return 256;
	}
	
	int tileHeight() {
		return 256;
	}
	
	vector<string> getTileUrls(Coordinate rawCoordinate) {
		vector<string> urls;
		if (rawCoordinate.row >= 0 && rawCoordinate.row < pow(2, rawCoordinate.zoom)) {
			Coordinate coordinate = sourceCoordinate(rawCoordinate);
			stringstream url;
			string subdomain = subdomains[(int)ofRandom(0, subdomains.size())];
            
            
			url << "http://" << subdomain << serverName << (int)coordinate.zoom << "/" << (int)coordinate.column << "/" << (int)coordinate.row << ".png";
			cout << rawCoordinate << " --> " << url.str() << endl;
			urls.push_back(url.str());
		}
		return urls;
	}
	
};

#endif