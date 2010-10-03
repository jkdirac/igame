file = [E_coli.xml]

MoDeL
{
	compartment id = [E_coli], name = [Escherichia coli], spatialDimensions = [3], size = [1E-14], units = [litre]
	{
		listOfInnerCompartmentPermitted
		{
			compartmentReference:[ribosome];
		}
	}
}

